#include "Indice2D.h"
#include "Indice1D.h"
#include "IndiceTools.h"
#include "cudaTools.h"
#include "Device.h"
#include "Lock.h"

#include "ConvolutionTextureMath.h"

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/
#define KERNEL_LENGTH 9*9
__device__ int mutex = 0;

texture<uchar4,2> textureRef;

__constant__ float CONST_MEM_KERNEL[KERNEL_LENGTH];

__host__ void init_Const_Memory_Kernel(float* ptrKernelDevice);
__host__ void init_textMemory (uchar4* ptrImageVideoDevice, int w, int h);
__host__ void unMapTextMemory();

//__global__ void convolutionTextureKernel(uchar4* ptrDevPixels, float* ptrDeviceNoyau, int k, int w, int h, float t);
__global__ void convolutionTextureKernel(uchar4* ptrDevPixels, int k, int w, int h, float t);

__global__ void colorToGreyTexture(uchar4* ptrDevPixels, int w, int h);

__global__ void affineTransformTexture(uchar4* ptrDevPixels, float a, float b, int w, int h, int offset);

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

/*----------------------------------------------------------------------*\
 |*			Implementation 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

__device__ void ecrasementTexture(uchar* tabSM, int halfThread)
    {
    const int TID_LOCAL = Indice1D::tidLocalBlock();
    const int NB_THREAD_BLOCK = Indice1D::nbThreadBlock();
    int s = TID_LOCAL;
    while(s<halfThread)
	{
	if(tabSM[s]>tabSM[s+halfThread]) // if tabSM not min
	    tabSM[s] = tabSM[s+halfThread];
	if(tabSM[NB_THREAD_BLOCK+s]<tabSM[NB_THREAD_BLOCK+s+halfThread]) // if tabSM not max
	    tabSM[NB_THREAD_BLOCK+s] = tabSM[NB_THREAD_BLOCK+s+halfThread];
	s+=NB_THREAD_BLOCK;
	}
    }

__device__ void reductionIntraBTexture(uchar* tabSM)
    {
    const int NB_THREAD = Indice1D::nbThread();
    const int NB_THREAD_BLOCK=Indice1D::nbThreadBlock();
    int halfThread = NB_THREAD_BLOCK/2;
    while(halfThread>=1)
	{
	ecrasementTexture(tabSM,halfThread);
	__syncthreads();
	halfThread/=2;
	}
    }

__device__ void reductionInterBTexture(uchar* tabSM, uchar* ptrDevResult)
    {
    const int TID_LOCAL = Indice1D::tidLocalBlock();
    const int NB_THREADS = Indice1D::nbThreadBlock();
    const int NB_BLOCKS = gridDim.x;
    const int BID = blockIdx.x;
    if(TID_LOCAL==0)
	{
	// bad idea with Lock, finish on CPU instead, only NB_BLOCKS items
	ptrDevResult[BID] = tabSM[0]; // min
	ptrDevResult[NB_BLOCKS+BID] = tabSM[NB_THREADS]; // max
	}

    }

__device__ void reductionIntraTTexture(uchar* tabSM, uchar4* ptrDevPixels,int n)
    {
    const int NB_THREAD = Indice1D::nbThread();
    const int TID = Indice1D::tid();
    const int TID_LOCAL = Indice1D::tidLocalBlock();

    int s = TID;
    uchar minCrtThread = 255;
    uchar maxCrtThread = 0;
    while(s<n)
	{
	uchar crtVal = ptrDevPixels[s].x;
	if(crtVal > maxCrtThread)
	    maxCrtThread = crtVal;
	if(crtVal < minCrtThread)
	    minCrtThread = crtVal;
	s+=NB_THREAD;
	}
    tabSM[TID_LOCAL] = minCrtThread;
    tabSM[Indice1D::nbThreadBlock()+TID_LOCAL] = maxCrtThread; // tabSM is 2*n size
    }

__global__ void colorToGreyTexture(uchar4* ptrDevPixels, int w, int h)
    {
    const int TID = Indice2D::tid();
    const int NB_THREAD = Indice2D::nbThread();

    const int WH=w*h;

    int s = TID;
    while(s<WH)
	{

	float x = ptrDevPixels[s].x;
	float y = ptrDevPixels[s].y;
	float z = ptrDevPixels[s].z;
	float average = (x/(float)3.0+y/(float)3.0+z/(float)3.0);
	ptrDevPixels[s].x = average;
	ptrDevPixels[s].y = average;
	ptrDevPixels[s].z = average;
	ptrDevPixels[s].w = 255;
	s += NB_THREAD;
	}
    }

__global__ void affineTransformTexture(uchar4* ptrDevPixels, float a, float b, int w, int h, int offset)
    {
    const int TID = Indice2D::tid();
    const int NB_THREAD = Indice2D::nbThread();

    const int WH=w*h;

    int s = TID;
    while(s<WH)
	{
	uchar newValue = (uchar)((float)(ptrDevPixels[s].x)*a+b);
	newValue += offset;
	if(newValue > 255)
	    newValue = 255;
	ptrDevPixels[s].x = newValue;
	ptrDevPixels[s].y = newValue;
	ptrDevPixels[s].z = newValue;
	s += NB_THREAD;
	}
    }

__global__ void convolutionTextureKernel(uchar4* ptrDevPixels,int k, int w, int h, float t)
    {
    ConvolutionTextureMath convMath = ConvolutionTextureMath(w, h);

    const int TID = Indice2D::tid();
    const int NB_THREAD = Indice2D::nbThread();

    const int WH=w*h;


    uchar4 color;


    int pixelI;
    int pixelJ;

    int s = TID;
    while (s < WH)
	{
	IndiceTools::toIJ(s, w, &pixelI, &pixelJ); // update (pixelI, pixelJ)
	const int KERN_SIZE =9;
	const int KERN_OFFSET=-4;
	uchar4 colorsVideo[9*9];
	int sk=0;
	for(int i=0;i<KERN_SIZE;i++){
	    int iTex = KERN_OFFSET+i;
	    for (int j=0;j<KERN_SIZE;j++){
	    int jTex=KERN_OFFSET+j;
	    colorsVideo[sk]=tex2D(textureRef,jTex+pixelJ,iTex+pixelI);



	    sk++;
	    }
	}

	convMath.colorIJ(&color,colorsVideo,CONST_MEM_KERNEL,KERN_SIZE); // update color
	ptrDevPixels[s] = color;
	s += NB_THREAD;
	}
    }


/*__global__ void convolutionTextureKernel(uchar4* ptrDevPixels, float* ptrDeviceNoyau,int k, int w, int h, float t)
    {
    ConvolutionTextureMath convMath = ConvolutionTextureMath(w, h);

    const int TID = Indice2D::tid();
    const int NB_THREAD = Indice2D::nbThread();

    const int WH=w*h;


    uchar4 color;


    int pixelI;
    int pixelJ;

    int s = TID;
    while (s < WH)
	{
	IndiceTools::toIJ(s, w, &pixelI, &pixelJ); // update (pixelI, pixelJ)
	const int KERN_SIZE =9;
	const int KERN_OFFSET=-4;
	uchar4 colorsVideo[9*9];
	int sk=0;
	for(int i=0;i<KERN_SIZE;i++){
	    int iTex = KERN_OFFSET+i;
	    for (int j=0;j<KERN_SIZE;j++){
	    int jTex=KERN_OFFSET+j;
	    colorsVideo[sk]=tex2D(textureRef,jTex+pixelJ,iTex+pixelI);



	    sk++;
	    }
	}

	convMath.colorIJ(&color,colorsVideo,ptrDeviceNoyau,KERN_SIZE); // update color
	ptrDevPixels[s] = color;
	s += NB_THREAD;
	}
    }*/


/*
 * ptrDevResult should contain min in [0] and max in [1]
 */
__global__ void findMinMaxTexture(uchar4* ptrDevPixels, uchar* ptrDevResult,int w, int h)
    {
    // one shared memory per block
    extern __shared__ uchar tabSM[];
    //const int TID_LOCAL = Indice1D::tidLocalBlock();

    int sizePtrDevPixels = w*h;
    reductionIntraTTexture(tabSM, ptrDevPixels,sizePtrDevPixels);
    reductionIntraBTexture(tabSM);
    reductionInterBTexture(tabSM, ptrDevResult);
    }

__host__ void init_textMemory (uchar4* ptrImageVideoDevice, int w, int h){

    textureRef.addressMode[0] = cudaAddressModeClamp; //par defaut
    textureRef.addressMode[1] = cudaAddressModeClamp; //par defaut
    textureRef.filterMode = cudaFilterModePoint; //par defaut
    textureRef.normalized = false; //coordonnÃ©e texture //par defau
    size_t pitch = w * sizeof(uchar4);
    cudaChannelFormatDesc channelDesc = cudaCreateChannelDesc<uchar4>();
        HANDLE_ERROR(cudaBindTexture2D(NULL, textureRef,ptrImageVideoDevice,channelDesc,w,h,pitch));
}

__host__ void unMapTextMemory(){
    cudaUnbindTexture(textureRef);
}
__host__ void init_Const_Memory_Kernel(float* ptrKernelDevice){

    size_t size = KERNEL_LENGTH*sizeof(float);
    int offset =0;
    HANDLE_ERROR(cudaMemcpyToSymbol(CONST_MEM_KERNEL, ptrKernelDevice, size, offset,cudaMemcpyDeviceToDevice));

}

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/


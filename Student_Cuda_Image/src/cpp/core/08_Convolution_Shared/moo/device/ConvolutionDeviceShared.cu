#include "Indice2D.h"
#include "Indice1D.h"
#include "IndiceTools.h"
#include "cudaTools.h"
#include "Device.h"
#include "Lock.h"

#include "ConvolutionMathShared.h"

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

__device__ int mutex = 0;

__global__ void convolutionKernelShared(uchar4* ptrDevPixels, float* ptrDeviceNoyau, int k, int w, int h,float t);

__global__ void colorToGreyShared(uchar4* ptrDevPixels, int w, int h);

__global__ void affineTransformShared(uchar4* ptrDevPixels, float a, float b, int w, int h, int offset);

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/


/*----------------------------------------------------------------------*\
 |*			Implementation 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

__device__ void ecrasementShared(uchar* tabSM, int halfThread)
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

__device__ void reductionIntraBShared(uchar* tabSM)
    {
    const int NB_THREAD = Indice1D::nbThread();
    const int NB_THREAD_BLOCK=Indice1D::nbThreadBlock();
    int halfThread = NB_THREAD_BLOCK/2;
    while(halfThread>=1)
	{
	ecrasementShared(tabSM,halfThread);
	__syncthreads();
	halfThread/=2;
	}
    }

__device__ void reductionInterBShared(uchar* tabSM, uchar* ptrDevResult)
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

__device__ void reductionIntraTShared(uchar* tabSM, uchar4* ptrDevPixels,int n)
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
    //printf("currentSum=%f PI=%f\n in reduce intrathread", sumCurrentThread,sumCurrentThread*DX);
    //cout<<"currentSum"<<sumCurrentThread<<endl;
    tabSM[TID_LOCAL] = minCrtThread;
    tabSM[Indice1D::nbThreadBlock()+TID_LOCAL] = maxCrtThread; // tabSM is 2*n size
    }

__global__ void colorToGreyShared(uchar4* ptrDevPixels, int w, int h)
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

__global__ void affineTransformShared(uchar4* ptrDevPixels, float a, float b, int w, int h, int offset)
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

__global__ void convolutionKernelShared(uchar4* ptrDevPixels, float* ptrDeviceNoyau, int k, int w, int h, float t)
    {

    extern __shared__ float convSM[];// 1 instance per block !

    ConvolutionMathShared convMath = ConvolutionMathShared(w, h);

    const int TID = Indice2D::tid();
    const int TID_LOCAL = Indice2D::tidLocal();
    const int NB_THREAD = Indice2D::nbThread();

    const int WH=w*h;

    uchar4 color;

    int pixelI;
    int pixelJ;

    int s = TID_LOCAL;
    if(s < (k*k))
	convSM[s] = ptrDeviceNoyau[s];
    __syncthreads();

    s = TID;
    while (s < WH)
	{
	IndiceTools::toIJ(s, w, &pixelI, &pixelJ); // update (pixelI, pixelJ)
	color = ptrDevPixels[s];
	convMath.colorIJ(&color,ptrDevPixels,convSM,k,pixelI, pixelJ, s); 	// update color
	ptrDevPixels[s] = color;
	s += NB_THREAD;
	}
    }

/*
 * ptrDevResult should contain min in [0] and max in [1]
 */
__global__ void findMinMaxShared(uchar4* ptrDevPixels, uchar* ptrDevResult,int w, int h)
    {
    // one shared memory per block
    extern __shared__ uchar tabSM[];
    //const int TID_LOCAL = Indice1D::tidLocalBlock();

    int sizePtrDevPixels = w*h;
    reductionIntraTShared(tabSM, ptrDevPixels,sizePtrDevPixels);
    reductionIntraBShared(tabSM);
    reductionInterBShared(tabSM, ptrDevResult);
    }

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/


#include <iostream>
#include <cstdio>
#include <assert.h>

#include "ConvolutionTexture.h"
//#include "ConvolutionMathTexture.h"
#include "Indice2D.h"
#include "IndiceTools.h"
#include "Device.h"
#include "MathTools.h"

using std::cout;
using std::endl;

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Imported	 	*|
 \*-------------------------------------*/

//extern __global__ void convolutionKernelTexture(texture<uchar4,2> tex, uchar4* ptrDevPixels, float* ptrDeviceNoyau, int k, int w, int h, float t);
extern __global__ void colorToGreyTexture(uchar4* ptrDevPixels, int w, int h);
extern __global__ void findMinMaxTexture(uchar4* ptrDevPixels, uchar* ptrDevResult,int w, int h);
extern __global__ void affineTransformTexture(uchar4* ptrDevPixels, float a, float b, int w, int h, int offset);

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

texture<uchar4, 2> textureRef;

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

/*----------------------------------------------------------------------*\
 |*			Implementation 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

__device__
void colorIJ(uchar4* ptrColor, float* ptrDeviceNoyau, int k, int i, int j, int s)
    {

    float sum = 0.0f;
    int ss = (int)(k*((float)k/2.0f));
    int k2 = k/2;
    for(int v = 1;v<=k2;v++)
	{
	for(int u = 1;u<=k2;u++)
	    {
	    // bas droite
	    sum+=ptrDeviceNoyau[(ss+v*k)+u]*tex2D(textureRef,j+u,i+v).x;
	    // haut droite
	    sum+=ptrDeviceNoyau[(ss-v*k)+u]*tex2D(textureRef,j+u,i-v).x;
	    // bas gauche
	    sum+=ptrDeviceNoyau[(ss+v*k)-u]*tex2D(textureRef,j-u,i+v).x;
	    // haut gauche
	    sum+=ptrDeviceNoyau[(ss-v*k)-u]*tex2D(textureRef,j-u,i-v).x;
	    }
	// bras east
	sum+=ptrDeviceNoyau[ss+v]*tex2D(textureRef,j,i+v).x;
	// bras west
	sum+=ptrDeviceNoyau[ss-v]*tex2D(textureRef,j,i-v).x;
	// bras south
	sum+=ptrDeviceNoyau[ss+v*k]*tex2D(textureRef,j+v,i).x;
	// bras north
	sum+=ptrDeviceNoyau[ss-v*k]*tex2D(textureRef,j-v,i).x;
	}
    // centre
    sum+=ptrDeviceNoyau[ss]*tex2D(textureRef,j,i).x;
    ptrColor->x = sum;
    ptrColor->y = sum;
    ptrColor->z = sum;

    ptrColor->w = 255; // opaque
    }

__global__ void convolutionKernelTexture(uchar4* ptrDevPixels, float* ptrDeviceNoyau, int k, int w, int h, float t)
    {

    extern __shared__ float convSM[];// 1 instance per block !

    //ConvolutionMathTexture convMath = ConvolutionMathTexture(w, h);

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
	colorIJ(&color,convSM,k,pixelI, pixelJ, s); 	// update color
	ptrDevPixels[s] = color;
	s += NB_THREAD;
	}
    }

/*-------------------------*\
 |*	Constructeur	    *|
 \*-------------------------*/

ConvolutionTexture::ConvolutionTexture()
    {
    // Inputs
    this->w = 640;
    this->h = 360;
    this->k = 9;

    // Tools
    this->dg = dim3(16, 1, 1); // disons a optimiser
    this->db = dim3(128, 1, 1); // disons a optimiser
    this->t=0;

    //Outputs
    this->title="[API Image Cuda] : Convolution CUDA";
    this->videoPath="/media/Data/Video/nasaFHD_short.avi";
    this->videoTitle="NASA FHD SHORT";

    this->videoPath="/media/Data/Video/neilPryde.avi";
    this->videoTitle="neilPryde";

    size_t sizeOctets=w*h*sizeof(uchar4);
    HANDLE_ERROR( cudaHostAlloc ((void**) &(this->ptrHostMemory), sizeOctets,cudaHostAllocDefault ) );

    this->captureur = new CaptureVideo(videoPath,videoTitle,this->ptrHostMemory);

    const int N = k*k;
    sizeConvSM = N*sizeof(float);

    HANDLE_ERROR( cudaHostAlloc ((void**) &(this->ptrHostNoyau), N*sizeof(float),cudaHostAllocDefault ) );

    fillDetourage(ptrHostNoyau);

    HANDLE_ERROR(cudaMalloc((void **)&ptrDeviceNoyau,N*sizeof(float)));
    HANDLE_ERROR(cudaMemcpy(ptrDeviceNoyau,ptrHostNoyau,N*sizeof(float),cudaMemcpyHostToDevice));


    sizeSM = 2*db.x*sizeof(uchar);
    sizeResult=2*dg.x*sizeof(uchar);
    ptrHostResult = (uchar*) malloc(sizeResult);

    // first contains min of each block, then max of each block
    HANDLE_ERROR(cudaMalloc((void**) &ptrDevResult, sizeResult));

    textureRef.filterMode= cudaFilterModePoint;
    textureRef.normalized=false; //ou true coordonnée texture (i,j)
    textureRef.addressMode[0] = cudaAddressModeClamp;
    textureRef.addressMode[1] = cudaAddressModeClamp;

    pitch = w * sizeof(uchar4); //taille en octets d'une ligne
    channelDesc = cudaCreateChannelDesc<uchar4>();

    //cout << endl<<"[CBI] Convolution dt =" << dt << endl;
    }

ConvolutionTexture::~ConvolutionTexture()
    {
    free(ptrHostResult);
    cudaFree(ptrDevResult);
    }

/*-------------------------*\
 |*	Methode		    *|
 \*-------------------------*/

/**
 * Noyau detourage 9x9
 */
void ConvolutionTexture::fillDetourage(float* ptrNoyau)
    {
    const int N = 9*9;
    // Tab auto temporaire
    float tab[N] =
	    {
		    0.0828, 0.1987, 0.3705, 0.5366, 0.6063, 0.5366, 0.3705, 0.1987, 0.0828, 0.1987, 0.4746, 0.8646, 1.1794, 1.2765, 1.1794, 0.8646, 0.4746, 0.1987, 0.3705, 0.8646, 1.3475, 1.0033, 0.4061, 1.0033, 1.3475, 0.8646, 0.3705, 0.5366, 1.1794, 1.0033, -2.8306, -6.4829, -2.8306, 1.0033, 1.1794, 0.5366, 0.6063, 1.2765, 0.4061, -6.4829, -12.7462, -6.4829, 0.4061, 1.2765, 0.6063, 0.5366, 1.1794, 1.0033, -2.8306, -6.4829, -2.8306, 1.0033, 1.1794, 0.5366, 0.3705, 0.8646, 1.3475, 1.0033, 0.4061, 1.0033, 1.3475, 0.8646, 0.3705, 0.1987, 0.4746, 0.8646, 1.1794, 1.2765, 1.1794, 0.8646, 0.4746, 0.1987, 0.0828, 0.1987, 0.3705, 0.5366, 0.6063, 0.5366, 0.3705, 0.1987, 0.0828
	    };

    for (int i = 1; i <= N; i++)
	{
	ptrNoyau[i - 1] = tab[i - 1] / 100.0f;
	}
    }

/**
 * Override
 * Call periodicly by the API
 */
void ConvolutionTexture::animationStep()
    {
    //t+=dt;
    }

/**
 * Override
 */
void ConvolutionTexture::runGPU(uchar4* ptrDevPixels)
    {
    Mat matImage = captureur->capturer();
    uchar4* image = CaptureVideo::castToUChar4(&matImage);

    HANDLE_ERROR(cudaMemcpy(ptrDevPixels,image,(w*h)*sizeof(ptrDevPixels[0]),cudaMemcpyHostToDevice));

    cudaBindTexture2D(NULL, textureRef,ptrDevPixels,channelDesc,w,h,pitch);

    colorToGreyTexture<<<dg,db>>>(ptrDevPixels,w,h);
    HANDLE_ERROR(cudaDeviceSynchronize());

    convolutionKernelTexture<<<dg,db,sizeConvSM>>>(ptrDevPixels,ptrDeviceNoyau,k,w,h,t);
    HANDLE_ERROR(cudaDeviceSynchronize());

    findMinMaxTexture<<<dg,db,sizeSM>>>(ptrDevPixels,ptrDevResult,w,h);
    HANDLE_ERROR(cudaMemcpy(ptrHostResult, ptrDevResult, sizeResult, cudaMemcpyDeviceToHost));

    uchar max = 0;
    uchar min = 255;
    for(int i = 0;i<dg.x;i++)
	{
	uchar crt = ptrHostResult[i];
	if(crt < min)
	    min = crt;
	crt = ptrHostResult[i+dg.x];
	if(crt > max)
	    max = crt;
	}
    // affine transformation
    float a = 255.0f/(float)(max-min);
    float b = 0;
    if(min != 0)
	b = 255.0f/((-max/(float)min)+1.0f);
    affineTransformTexture<<<dg,db>>>(ptrDevPixels, a, b, w, h,0);
    //printf("min: %d, max: %d\n",min,max);
    }

/*--------------*\
 |*	get	 *|
 \*--------------*/

/**
 * Override
 */
float ConvolutionTexture::getT(void)
    {
    return t;
    }

/**
 * Override
 */
int ConvolutionTexture::getW(void)
    {
    return w;
    }

/**
 * Override
 */
int ConvolutionTexture::getH(void)
    {
    return  h;
    }

/**
 * Override
 */
string ConvolutionTexture::getTitle(void)
    {
    return title;
    }

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/


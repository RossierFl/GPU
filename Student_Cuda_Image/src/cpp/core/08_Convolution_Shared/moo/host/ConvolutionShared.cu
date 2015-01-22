#include <iostream>
#include <cstdio>
#include <assert.h>

#include "ConvolutionShared.h"
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

extern __global__ void convolutionKernelShared(uchar4* ptrDevPixels, float* ptrDeviceNoyau, int k, int w, int h, float t);
extern __global__ void colorToGreyShared(uchar4* ptrDevPixels, int w, int h);
extern __global__ void findMinMaxShared(uchar4* ptrDevPixels, uchar* ptrDevResult,int w, int h);
extern __global__ void affineTransformShared(uchar4* ptrDevPixels, float a, float b, int w, int h, int offset);

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

/*----------------------------------------------------------------------*\
 |*			Implementation 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

/*-------------------------*\
 |*	Constructeur	    *|
 \*-------------------------*/

ConvolutionShared::ConvolutionShared()
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
    this->title="[API Image Cuda] : Convolution CUDA Shared";
    //this->videoPath="/media/Data/Video/nasaFHD_short.avi";
    //this->videoTitle="NASA FHD SHORT";

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

    //cout << endl<<"[CBI] Convolution dt =" << dt << endl;
    }

ConvolutionShared::~ConvolutionShared()
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
void ConvolutionShared::fillDetourage(float* ptrNoyau)
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
void ConvolutionShared::animationStep()
    {
    //t+=dt;
    }

/**
 * Override
 */
void ConvolutionShared::runGPU(uchar4* ptrDevPixels)
    {
    Chronos chrono;
    Mat matImage = captureur->capturer();
    uchar4* image = CaptureVideo::castToUChar4(&matImage);
    HANDLE_ERROR(cudaMemcpy(ptrDevPixels,image,(w*h)*sizeof(ptrDevPixels[0]),cudaMemcpyHostToDevice));
    colorToGreyShared<<<dg,db>>>(ptrDevPixels,w,h);
    HANDLE_ERROR(cudaDeviceSynchronize());
    convolutionKernelShared<<<dg,db,sizeConvSM>>>(ptrDevPixels,ptrDeviceNoyau,k,w,h,t);
    HANDLE_ERROR(cudaDeviceSynchronize());
    findMinMaxShared<<<dg,db,sizeSM>>>(ptrDevPixels,ptrDevResult,w,h);
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
    affineTransformShared<<<dg,db>>>(ptrDevPixels, a, b, w, h,0);
    //printf("min: %d, max: %d\n",min,max);
    cudaDeviceSynchronize();
    chrono.stop();
    cout << "ElapseTime:  " << chrono.getDeltaTime()<< " (s)" << endl;
    }

/*--------------*\
 |*	get	 *|
 \*--------------*/

/**
 * Override
 */
float ConvolutionShared::getT(void)
    {
    return t;
    }

/**
 * Override
 */
int ConvolutionShared::getW(void)
    {
    return w;
    }

/**
 * Override
 */
int ConvolutionShared::getH(void)
    {
    return  h;
    }

/**
 * Override
 */
string ConvolutionShared::getTitle(void)
    {
    return title;
    }

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/


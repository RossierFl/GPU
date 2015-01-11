#include <iostream>
#include <cstdio>
#include <assert.h>

#include "Convolution.h"
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

extern __global__ void convolutionKernel(uchar4* ptrDevPixels, float* ptrDeviceNoyau, int k, int w, int h, float t);
extern __global__ void colorToGrey(uchar4* ptrDevPixels, int w, int h);

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

Convolution::Convolution(int w, int h,float dt)
    {
    // Inputs
    this->w = w;
    this->h = h;
    this->dt=dt;
    this->k = 9;

    // Tools
    this->dg = dim3(8, 8, 1); // disons a optimiser
    this->db = dim3(16, 16, 1); // disons a optimiser
    this->t=0;

    //Outputs
    this->title="[API Image Cuda] : Convolution CUDA";
    this->videoPath="/media/Data/Video/nasaFHD_short.avi";
    this->videoTitle="NASA FHD SHORT";

    size_t sizeOctets=w*h*sizeof(uchar4);
    HANDLE_ERROR( cudaHostAlloc ((void**) &(this->ptrHostMemory), sizeOctets,cudaHostAllocDefault ) );

    this->captureur = new CaptureVideo(videoPath,videoTitle,this->ptrHostMemory);

    const int N = k*k;

    printf("N: %d, k: %d, half of k: %d, ss: %d\n",N,k,k/2,(int)(k*((float)k/2.0f)));

    HANDLE_ERROR( cudaHostAlloc ((void**) &(this->ptrHostNoyau), N*sizeof(float),cudaHostAllocDefault ) );

    fillDetourage(ptrHostNoyau);

    HANDLE_ERROR(cudaMalloc((void **)&ptrDeviceNoyau,N*sizeof(float)));
    HANDLE_ERROR(cudaMemcpy(ptrDeviceNoyau,ptrHostNoyau,N*sizeof(float),cudaMemcpyHostToDevice));

    //cout << endl<<"[CBI] Convolution dt =" << dt << endl;
    }

Convolution::~Convolution()
    {
    // rien
    }

/*-------------------------*\
 |*	Methode		    *|
 \*-------------------------*/

/**
 * Noyau detourage 9x9
 */
void Convolution::fillDetourage(float* ptrNoyau)
    {
    const int N = 9*9;
    // Tab auto temporaire
    float tab[N] =
	    {
		    0.0828, 0.1987, 0.3705, 0.5366, 0.6063, 0.5366, 0.3705, 0.1987, 0.0828, 0.1987, 0.4746, 0.8646, 1.1794, 1.2765, 1.1794, 0.8646, 0.4746, 0.1987, 0.3705, 0.8646, 1.3475, 1.0033, 0.4061, 1.0033, 1.3475, 0.8646, 0.3705, 0.5366, 1.1794, 1.0033, -2.8306, -6.4829, -2.8306, 1.0033, 1.1794, 0.5366, 0.6063, 1.2765, 0.4061, -6.4829, -12.7462, -6.4829, 0.4061, 1.2765, 0.6063, 0.5366, 1.1794, 1.0033, -2.8306, -6.4829, -2.8306, 1.0033, 1.1794, 0.5366, 0.3705, 0.8646, 1.3475, 1.0033, 0.4061, 1.0033, 1.3475, 0.8646, 0.3705, 0.1987, 0.4746, 0.8646, 1.1794, 1.2765, 1.1794, 0.8646, 0.4746, 0.1987, 0.0828, 0.1987, 0.3705, 0.5366, 0.6063, 0.5366, 0.3705, 0.1987, 0.0828
	    };

    for (int i = 1; i <= N; i++)
	{
	ptrNoyau[i - 1] = tab[i - 1] / 100;
	}
    }

/**
 * Override
 * Call periodicly by the API
 */
void Convolution::animationStep()
    {
    t+=dt;
    }

/**
 * Override
 */
void Convolution::runGPU(uchar4* ptrDevPixels)
    {
    Mat matImage = captureur->capturer();
    uchar4* image = CaptureVideo::castToUChar4(&matImage);
    HANDLE_ERROR(cudaMemcpy(ptrDevPixels,image,(w*h)*sizeof(ptrDevPixels[0]),cudaMemcpyHostToDevice));
    colorToGrey<<<dg,db>>>(ptrDevPixels,w,h);
    HANDLE_ERROR(cudaDeviceSynchronize());
    convolutionKernel<<<dg,db>>>(ptrDevPixels,ptrDeviceNoyau,k,w,h,t);
    HANDLE_ERROR(cudaDeviceSynchronize());
    }

/*--------------*\
 |*	get	 *|
 \*--------------*/

/**
 * Override
 */
float Convolution::getT(void)
    {
    return t;
    }

/**
 * Override
 */
int Convolution::getW(void)
    {
    return w;
    }

/**
 * Override
 */
int Convolution::getH(void)
    {
    return  h;
    }

/**
 * Override
 */
string Convolution::getTitle(void)
    {
    return title;
    }

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/


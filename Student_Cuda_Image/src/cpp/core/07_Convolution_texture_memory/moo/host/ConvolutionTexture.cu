#include <iostream>
#include <cstdio>
#include <assert.h>

#include "ConvolutionTexture.h"
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
extern __host__ void init_Const_Memory_Kernel(float* ptrKernelDevice);
extern __host__ void init_textMemory (uchar4* ptrImageVideoDevice, int w, int h);
extern __host__ void unMapTextMemory();
//extern __global__ void convolutionTextureKernel(uchar4* ptrDevPixels, float* ptrDeviceNoyau,int k, int w, int h, float t);
extern __global__ void convolutionTextureKernel(uchar4* ptrDevPixels,int k, int w, int h, float t);
extern __global__ void colorToGreyTexture(uchar4* ptrDevPixels, int w, int h);
extern __global__ void findMinMaxTexture(uchar4* ptrDevPixels, uchar* ptrDevResult,int w, int h);
extern __global__ void affineTransformTexture(uchar4* ptrDevPixels, float a, float b, int w, int h, int offset);

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

ConvolutionTexture::ConvolutionTexture()
    {
    // Inputs
    this->w = 640;
    this->h = 360;
    this->k = 9;

    // Tools
    this->dg = dim3(16, 1, 1); // disons a optimiser
    this->db = dim3(32, 1, 1); // disons a optimiser
    this->t=0;

    //Outputs
    this->title="[API Image Cuda] : ConvolutionTexture CUDA";
    this->videoPath="/media/Data/Video/nasaFHD_short.avi";
    this->videoTitle="NASA FHD SHORT";

    this->videoPath="/media/Data/Video/neilPryde.avi";
    this->videoTitle="neilPryde";

    size_t sizeOctets=w*h*sizeof(uchar4);
    HANDLE_ERROR( cudaHostAlloc ((void**) &(this->ptrHostMemory), sizeOctets,cudaHostAllocDefault ) );

    this->captureur = new CaptureVideo(videoPath,videoTitle,this->ptrHostMemory);

    const int N = k*k;

    HANDLE_ERROR( cudaHostAlloc ((void**) &(this->ptrHostNoyau), N*sizeof(float),cudaHostAllocDefault ) );

    fillDetourage(ptrHostNoyau);

    HANDLE_ERROR(cudaMalloc((void **)&ptrDeviceNoyau,N*sizeof(float)));
    HANDLE_ERROR(cudaMemcpy(ptrDeviceNoyau,ptrHostNoyau,N*sizeof(float),cudaMemcpyHostToDevice));
    init_Const_Memory_Kernel(ptrDeviceNoyau);


    sizeSM = 2*db.x*sizeof(uchar);
    sizeResult=2*dg.x*sizeof(uchar);
    ptrHostResult = (uchar*) malloc(sizeResult);

    // first contains min of each block, then max of each block
    HANDLE_ERROR(cudaMalloc((void**) &ptrDevResult, sizeResult));

    // Conteneur de l'image capturess
    int sizeOfVideoImage=h*w*sizeof(uchar4);
    HANDLE_ERROR(cudaMalloc(&ptrImageVideoDevice,sizeOfVideoImage));

    //cout << endl<<"[CBI] ConvolutionTexture dt =" << dt << endl;
    }

ConvolutionTexture::~ConvolutionTexture()
    {
    free(ptrHostResult);
    cudaFree(ptrDevResult);
    cudaFree(ptrImageVideoDevice);
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
    //Copie de l'image dans le GPU et binder avec le mode texture
    uchar4* image = CaptureVideo::castToUChar4(&matImage);
    HANDLE_ERROR(cudaMemcpy(ptrImageVideoDevice,image,(w*h)*sizeof(uchar4),cudaMemcpyHostToDevice));

   // init_textMemory (ptrImageVideoDevice,  w,  h);
    init_textMemory (ptrImageVideoDevice,  w,  h);
     //taille en octets d'une ligne

    colorToGreyTexture<<<dg,db>>>(ptrImageVideoDevice,w,h);
    HANDLE_ERROR(cudaDeviceSynchronize());
    //convolutionTextureKernel<<<dg,db>>>(ptrDevPixels, ptrDeviceNoyau,  k,  w,  h,  t);//Sans memory constant
    convolutionTextureKernel<<<dg,db>>>(ptrDevPixels,  k,  w,  h,  t);
    HANDLE_ERROR(cudaPeekAtLastError());
   // convolutionTextureKernel<<<dg,db>>>(ptrImageVideoDevice,ptrDeviceNoyau,k,w,h,t);
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

    unMapTextMemory();
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


#include <assert.h>

#include "HeatTransfert.h"
#include "Device.h"
#include "MathTools.h"
#include <stdio.h>

#define NB_ITERATION_AVEUGLE 2

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Imported	 	*|
 \*-------------------------------------*/

extern __global__ void diffusion(float* ptrDevImageA,float* ptrDevImageB, int w, int h, float k, bool imgAIsInput);
extern __global__ void ecrasement(float* ptrDevInputHeater, float* ptrDevInputImage,float* ptrDevOutput, int w, int h);
extern __global__ void toScreenImageHSB(CalibreurCuda calibreurCuda,float* ptrDevInput, uchar4* ptrDevImage, int w, int h);

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

HeatTransfert::HeatTransfert(int w, int h, float k):calibreurCuda(0.0,1.0,0.7,0.0)
    {
    // Inputs
    this->w = w;
    this->h = h;
    this->k = k;
    // Tools
    this->dg = dim3(8, 8, 1); // disons a optimiser
    this->db = dim3(16, 16, 1); // disons a optimiser


    //Outputs
    this->title = "[API Image] : HeatTransfert CUDA";

    // Check:
    Device::assertDim(dg, db);
    assert(w == h);
    size_t sizeImages = w*h*sizeof(float);
    //init
    //imageInit all to zero
    HANDLE_ERROR(cudaMalloc((void**) &ptrDevImageInit, sizeImages)); // Device memory allocation (*)
    HANDLE_ERROR(cudaMemset(ptrDevImageInit,0,sizeImages)) ;

    HANDLE_ERROR(cudaMalloc((void**) &ptrDevImageA, sizeImages)); // Device memory allocation (*)
    HANDLE_ERROR(cudaMemset(ptrDevImageA,0,sizeImages)) ;

    HANDLE_ERROR(cudaMalloc((void**) &ptrDevImageB, sizeImages)); // Device memory allocation (*)
    HANDLE_ERROR(cudaMemset(ptrDevImageB,0,sizeImages)) ;

    //imageHeater all zero with some heater or "cooler"
    HANDLE_ERROR(cudaMalloc((void**) &ptrDevImageHeater, sizeImages)); // Device memory allocation (*)
    HANDLE_ERROR(cudaMemset(ptrDevImageHeater,0,sizeImages)) ;

    float* ptrHostImageHeater = new float[w*h];
    memset(ptrHostImageHeater,0,sizeImages);

    // init
//    for(int i=0;i<=h;i++)
//	{
//	for(int j=0;j<=w;j++)
//	    {
//	    ptrHostImageHeater[i*h+j]=0.0;
//	    }
//	}
    //single cooler point
    ptrHostImageHeater[295*h+400] = 0.2;
    ptrHostImageHeater[400*h+295] = 0.2;
    ptrHostImageHeater[505*h+400] = 0.2;
    ptrHostImageHeater[400*h+505] = 0.2;

    //main heater
    for(int i=300;i<=500;i++)
	{
	for(int j=300;j<=500;j++)
	    {
	    ptrHostImageHeater[i*h+j] = 1.0;
	    }
	}

    //north cooler
    for(int i=179;i<=195;i++)
	{
	for(int j=179;j<=195;j++)
	    {
	    ptrHostImageHeater[i*h+j] = 0.2;
	    }
	for(int j=605;j<=621;j++)
	    {
	    ptrHostImageHeater[i*h+j] = 0.2;
	    }
	}

    //south cooler
    for(int i=605;i<=621;i++)
	{
	for(int j=179;j<=195;j++)
	    {
	    ptrHostImageHeater[i*h+j] = 0.2;
	    }
	for(int j=605;j<=621;j++)
	    {
	    ptrHostImageHeater[i*h+j] = 0.2;
	    }
	}

    // host --> device
    HANDLE_ERROR(cudaMemcpy(ptrDevImageHeater,  ptrHostImageHeater, sizeImages, cudaMemcpyHostToDevice));// Host -> Device
    delete [] ptrHostImageHeater;

    ecrasement<<<dg,db>>>(ptrDevImageHeater,ptrDevImageA,ptrDevImageA, w, h);

    Device::synchronize();
    Device::checkKernelError("heatTransfertEcrasement");

    }

HeatTransfert::~HeatTransfert()
    {
    HANDLE_ERROR(cudaFree(ptrDevImageHeater));
    HANDLE_ERROR(cudaFree(ptrDevImageInit));
    HANDLE_ERROR(cudaFree(ptrDevImageA));
    HANDLE_ERROR(cudaFree(ptrDevImageB));
    }

/*-------------------------*\
 |*	Methode		    *|
 \*-------------------------*/

/**
 * Override
 */
void HeatTransfert::animationStep()
    {
    }

/**
 * Override
 */
void HeatTransfert::runGPU(uchar4* ptrDevPixels)
    {

    float* iterationOutput;
    for(int i=0;i<=NB_ITERATION_AVEUGLE;i++)
	{
	diffusion<<<dg,db>>>(ptrDevImageA,ptrDevImageB, w, h, k, (i+1)%2);
	Device::synchronize();


	if((i+1)%2==1)
	    iterationOutput=ptrDevImageB;
	else
	    iterationOutput=ptrDevImageA;

	ecrasement<<<dg,db>>>(ptrDevImageHeater,iterationOutput,iterationOutput, w, h);
	Device::synchronize();
	}

    toScreenImageHSB<<<dg,db>>>(this->calibreurCuda, iterationOutput,ptrDevPixels, w, h);
    }


/*--------------*\
 |*	get	 *|
 \*--------------*/

/**
 * Override
 */
float HeatTransfert::getT(void)
    {
    return 0.0;
    }

/**
 * Override
 */
int HeatTransfert::getW(void)
    {
    return w;
    }

/**
 * Override
 */
int HeatTransfert::getH(void)
    {
    return h;
    }

/**
 * Override
 */
string HeatTransfert::getTitle(void)
    {
    return title;
    }

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/


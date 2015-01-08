#include <assert.h>

#include "MandelbrotJuliaMGPU.h"
#include "Device.h"
#include "MathTools.h"
#include <stdio.h>

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Imported	 	*|
 \*-------------------------------------*/

__global__ void fractale(uchar4* ptrDevPixels, int w, int h, DomaineMath domaineMath, int n, float t,
	int isJulia, double c1, double c2);

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

MandelbrotJuliaMGPU::MandelbrotJuliaMGPU(int w, int h, float dt, int n, int isJulia,
	double c1, double c2, double x1, double y1, double x2, double y2) :
								variateurAnimation(IntervalF(30, 100), dt)
    {
    // Inputs
    this->w = w;
    this->h = h;
    this->n = n;

    this->c1 = c1;
    this->c2 = c2;

    this->isJulia = isJulia;

    // Tools
    this->dg = dim3(8, 8, 1); // disons a optimiser
    this->db = dim3(16, 16, 1); // disons a optimiser
    this->t = 0;
    ptrDomaineMathInit=new DomaineMath(x1,y1,x2,y2);

    //Outputs
    this->title = "[API Image Fonctionelle] : Mandelbrot Julia zoomable CUDA";

    // Check:
    //print(dg, db);
    Device::assertDim(dg, db);

    Device::p2pEnableALL();

    nbGPUs = 3;
    splittedH = h/nbGPUs;
    tailleSplitted = w*splittedH*sizeof(uchar4);

    for(int i = 1;i<nbGPUs;i++)
	{
	cudaSetDevice(i);
	HANDLE_ERROR(cudaMalloc((void**)&ptrDevZoneMemGPU[i],tailleSplitted));
	}
    cudaSetDevice(0);

    assert(w == h);
    }

MandelbrotJuliaMGPU::~MandelbrotJuliaMGPU()
    {
    delete ptrDomaineMathInit;
    }

/*-------------------------*\
 |*	Methode		    *|
 \*-------------------------*/

/**
 * Override
 */
void MandelbrotJuliaMGPU::animationStep()
    {
    this->t = variateurAnimation.varierAndGet(); // in [30,100]
    }

/**
 * Override
 */
void MandelbrotJuliaMGPU::runGPU(uchar4* ptrDevPixels, const DomaineMath& domaineMath)
    {
    for(int i = 0;i<nbGPUs;i++)
	{
	cudaSetDevice(i);
	int offset = w*splittedH;
	uchar4* ptrDevBandISrc = ptrDevPixels+offset;
	if(i == 0)
	    {
	    fractale<<<dg,db>>>(ptrDevPixels,w,splittedH,domaineMath,getT(),t,isJulia,c1,c2);
	    }
	else if(i > 0)
	    {
	    fractale<<<dg,db>>>(ptrDevZoneMemGPU[i],w,splittedH,domaineMath,getT(),t,isJulia,c1,c2);
	    HANDLE_ERROR(cudaMemcpy(ptrDevPixels+offset,ptrDevZoneMemGPU[i],tailleSplitted));
	    }
	}
    cudaSetDevice(0);
    //cudaDeviceSynchronize();
    }

/*--------------*\
 |*	get	 *|
 \*--------------*/

/**
 * Override
 */
DomaineMath* MandelbrotJuliaMGPU::getDomaineMathInit(void)
    {
    return ptrDomaineMathInit;
    }

/**
 * Override
 */
float MandelbrotJuliaMGPU::getT(void)
    {
    return t;
    }

/**
 * Override
 */
int MandelbrotJuliaMGPU::getW(void)
    {
    return w;
    }

/**
 * Override
 */
int MandelbrotJuliaMGPU::getH(void)
    {
    return h;
    }

/**
 * Override
 */
string MandelbrotJuliaMGPU::getTitle(void)
    {
    return title;
    }

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/


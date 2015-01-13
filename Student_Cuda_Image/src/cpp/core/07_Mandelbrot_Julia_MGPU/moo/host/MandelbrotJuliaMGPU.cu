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

__global__ void fractaleMGPU(uchar4* ptrDevPixels, int w, int h, DomaineMath domaineMath, int n, float t,
	int isJulia, double c1, double c2, int offset);

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
    this->title = "[API Image Fonctionelle] : Mandelbrot Julia multi-gpu zoomable CUDA";

    // Check:
    //print(dg, db);
    Device::assertDim(dg, db);

    Device::p2pEnableALL();

    nbGPUs = 3;
    splittedH = h/nbGPUs;
    tailleSplitted = w*splittedH*sizeof(uchar4);

    //ptrDevZoneMemGPU = (uchar4**) malloc(nbGPUs-1*sizeof(uchar4*));

    //    for(int i = 1;i<nbGPUs;i++)
    //	{
    //
    //	}
    cudaSetDevice(1);
    HANDLE_ERROR(cudaMalloc((void**)&ptrDevGpu1,tailleSplitted));
    cudaSetDevice(2);
    HANDLE_ERROR(cudaMalloc((void**)&ptrDevGpu2,tailleSplitted));
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
    /*
     * TODO implement OMP, but if no OMP, ok runs fine and quick without it
     */
    //    for(int i = 0;i<nbGPUs;i++)
    //	{
    cudaSetDevice(0);
    //	if(i == 0)
    //	    {
    int offset = 0;
    fractaleMGPU<<<dg,db>>>(ptrDevPixels,w,splittedH,domaineMath,getT(),t,isJulia,c1,c2,offset);
    //}
    //	else if(i > 0)
    //	    {
    cudaSetDevice(1);
    offset = w*splittedH;
    uchar4* ptrDevBandISrc = ptrDevPixels+offset;
    fractaleMGPU<<<dg,db>>>(ptrDevGpu1,w,splittedH,domaineMath,getT(),t,isJulia,c1,c2,offset);
    HANDLE_ERROR(cudaMemcpy(ptrDevBandISrc,ptrDevGpu1,tailleSplitted,cudaMemcpyDeviceToDevice));
    cudaSetDevice(2);
    offset = 2*w*splittedH;
    ptrDevBandISrc = ptrDevPixels+offset;
    fractaleMGPU<<<dg,db>>>(ptrDevGpu2,w,splittedH,domaineMath,getT(),t,isJulia,c1,c2,offset);
    HANDLE_ERROR(cudaMemcpy(ptrDevBandISrc,ptrDevGpu2,tailleSplitted,cudaMemcpyDeviceToDevice));

    // }
    //}

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


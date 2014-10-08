#include <assert.h>

#include "MandelbrotJulia.h"
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

MandelbrotJulia::MandelbrotJulia(int w, int h, float dt, int n, int isJulia,
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
    assert(w == h);
    }

MandelbrotJulia::~MandelbrotJulia()
    {
   delete ptrDomaineMathInit;
    }

/*-------------------------*\
 |*	Methode		    *|
 \*-------------------------*/

/**
 * Override
 */
void MandelbrotJulia::animationStep()
    {
    this->t = variateurAnimation.varierAndGet(); // in [30,100]
    }

/**
 * Override
 */
void MandelbrotJulia::runGPU(uchar4* ptrDevPixels, const DomaineMath& domaineMath)
    {
    fractale<<<dg,db>>>(ptrDevPixels,w,h,domaineMath,getT(),t,isJulia,c1,c2);
    //cudaDeviceSynchronize();
    }

/*--------------*\
 |*	get	 *|
 \*--------------*/

/**
 * Override
 */
DomaineMath* MandelbrotJulia::getDomaineMathInit(void)
    {
    return ptrDomaineMathInit;
    }

/**
 * Override
 */
float MandelbrotJulia::getT(void)
    {
    return t;
    }

/**
 * Override
 */
int MandelbrotJulia::getW(void)
    {
    return w;
    }

/**
 * Override
 */
int MandelbrotJulia::getH(void)
    {
    return h;
    }

/**
 * Override
 */
string MandelbrotJulia::getTitle(void)
    {
    return title;
    }

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/


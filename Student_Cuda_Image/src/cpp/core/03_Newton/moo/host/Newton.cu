#include <assert.h>

#include "Newton.h"
#include "Device.h"
#include "MathTools.h"

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Imported	 	*|
 \*-------------------------------------*/

__global__ void newton(uchar4* ptrDevPixels, int w, int h, DomaineMath domaineMath, int n, float t);

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

Newton::Newton(int w, int h, float dt, int n) :
	variateurAnimation(IntervalF(0, 2 * PI), dt)
    {
    // Inputs
    this->w = w;
    this->h = h;
    this->n = n;

    // Tools
    this->dg = dim3(8, 8, 1); // disons a optimiser
    this->db = dim3(16, 16, 1); // disons a optimiser
    this->t = 0;
    ptrDomaineMathInit=new DomaineMath(0,0,2*PI,2*PI);

    //Outputs
    this->title = "[API Image Fonctionelle] : Newton zoomable CUDA";

    // Check:
    //print(dg, db);
    Device::assertDim(dg, db);
    assert(w == h);
    }

Newton::~Newton()
    {
   delete ptrDomaineMathInit;
    }

/*-------------------------*\
 |*	Methode		    *|
 \*-------------------------*/

/**
 * Override
 */
void Newton::animationStep()
    {
    this->t = variateurAnimation.varierAndGet(); // in [0,2pi]
    }

/**
 * Override
 */
void Newton::runGPU(uchar4* ptrDevPixels, const DomaineMath& domaineMath)
    {
    newton<<<dg,db>>>(ptrDevPixels,w,h,domaineMath,n,t);
    }

/*--------------*\
 |*	get	 *|
 \*--------------*/

/**
 * Override
 */
DomaineMath* Newton::getDomaineMathInit(void)
    {
    return ptrDomaineMathInit;
    }

/**
 * Override
 */
float Newton::getT(void)
    {
    return t;
    }

/**
 * Override
 */
int Newton::getW(void)
    {
    return w;
    }

/**
 * Override
 */
int Newton::getH(void)
    {
    return h;
    }

/**
 * Override
 */
string Newton::getTitle(void)
    {
    return title;
    }

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/


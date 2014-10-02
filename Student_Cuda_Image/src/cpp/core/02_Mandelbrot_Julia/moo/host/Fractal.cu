#include <assert.h>

#include "Fractal.h"
#include "Device.h"
#include "MathTools.h"

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Imported	 	*|
 \*-------------------------------------*/

__global__ void fractal(uchar4* ptrDevPixels, int w, int h, DomaineMath domaineMath, int n, float t);

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

Fractal::Fractal(int w, int h, float dt, int n) :
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
    this->title = "[API Image Fonctionelle] : Fractal zoomable CUDA";

    // Check:
    //print(dg, db);
    Device::assertDim(dg, db);
    assert(w == h);
    }

Fractal::~Fractal()
    {
   delete ptrDomaineMathInit;
    }

/*-------------------------*\
 |*	Methode		    *|
 \*-------------------------*/

/**
 * Override
 */
void Fractal::animationStep()
    {
    this->t = variateurAnimation.varierAndGet(); // in [0,2pi]
    }

/**
 * Override
 */
void Fractal::runGPU(uchar4* ptrDevPixels, const DomaineMath& domaineMath)
    {
    //TODO
    }

/*--------------*\
 |*	get	 *|
 \*--------------*/

/**
 * Override
 */
DomaineMath* Fractal::getDomaineMathInit(void)
    {
    return ptrDomaineMathInit;
    }

/**
 * Override
 */
float Fractal::getT(void)
    {
    return t;
    }

/**
 * Override
 */
int Fractal::getW(void)
    {
    return w;
    }

/**
 * Override
 */
int Fractal::getH(void)
    {
    return h;
    }

/**
 * Override
 */
string Fractal::getTitle(void)
    {
    return title;
    }

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/


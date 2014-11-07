#include <assert.h>

#include "Fractal.h"
#include "Device.h"
#include "MathTools.h"
#include <stdio.h>

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Imported	 	*|
 \*-------------------------------------*/

__global__ void fractal(uchar4* ptrDevPixels, int w, int h, DomaineMath domaineMath, int n, double cx, double cyi, bool isJulia);

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

Fractal::Fractal(unsigned int w, unsigned int h, unsigned int nMin, unsigned int nMax, double cx, double cyi, bool isJulia, double x0, double x1, double y0, double y1) :
	variateurAnimation(IntervalF(nMin, nMax), 1)
    {
    // Inputs
    this->w = w;
    this->h = h;
    this->n = nMin;
    this->cx = cx;
    this->cyi = cyi;
    this->isJulia = isJulia;
    this->x0=x0;
    this->x1=x1;
    this->y0=y0;
    this->y1=y1;

    // Tools
    this->dg = dim3(16, 16, 1); // disons a optimiser
    this->db = dim3(8, 8, 1); // disons a optimiser
    this->t = 0;
    this->ptrDomaineMathInit=new DomaineMath(x0,y0,x1,y1);

    //Outputs
    this->title = "[API Image Fonctionelle] : Fractal CUDA";

    // Check:
    //print(dg, db);
    Device::checkDimOptimiser(dg, db);
    //assert(w == h);
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
    this->n = variateurAnimation.varierAndGet(); // in [0,2pi]
    }

/**
 * Override
 */
void Fractal::runGPU(uchar4* ptrDevPixels, const DomaineMath& domaineMath)
    {
    fractal<<<dg,db>>>(ptrDevPixels,w,h,domaineMath, n, cx, cyi, isJulia);
    //Device::synchronize();
    //Device::checkKernelError("fractal");
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
    return n;
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


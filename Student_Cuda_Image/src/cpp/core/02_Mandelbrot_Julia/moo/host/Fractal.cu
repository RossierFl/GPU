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

__global__ void fractal(uchar4* ptrDevPixels, int w, int h,bool julia, DomaineMath domaineMath, int n,double cx, double cy);
//uchar4* ptrDevPixels,int w, int h,bool julia,DomaineMath domaineMath, int n,double cx, double cy

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

Fractal::Fractal(int w, int h, float dt,  int nMin,int nMax,bool julia,double cx,double cy,double xMin, double xMax, double yMin, double yMax) :
	variateurAnimation(IntervalI(nMin,nMax), dt)
    {
    // Inputs
    this->w = w;
    this->h = h;
    this->julia = julia;
    this->cx = cx;
    this->cy = cy;
    this->n = nMin;
    // Tools
    this->dg = dim3(8, 8, 1); // disons a optimiser
    this->db = dim3(16, 16, 1); // disons a optimiser
    ptrDomaineMathInit=new DomaineMath(xMin,yMin,xMax,yMax);

    //Outputs
    this->title = "[API Image Fonctionelle] : Fractal zoomable CUDA";

    // Check:
    //print(dg, db);
    Device::assertDim(dg, db);
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
    fractal<<<dg,db>>>(ptrDevPixels,this->w,this->h,this->julia,*ptrDomaineMathInit,this->n,this->cx,this->cy);
    //uchar4* ptrDevPixels,int w, int h,bool julia,DomaineMath domaineMath, int n,double cx, double cy
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
    t=n;
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


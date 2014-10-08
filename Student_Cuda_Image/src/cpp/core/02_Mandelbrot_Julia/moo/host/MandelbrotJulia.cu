#include <iostream>
#include <assert.h>


#include "MathTools.h"

#include "MandelbrotJulia.h"
#include "Device.h"
#include "DomaineMath.h"

using std::cout;
using std::endl;

/*----------------------------------------------------------------------*\
 |*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Imported	 	*|
 \*-------------------------------------*/

__global__ void MandelbrotJulia(uchar4* ptrDevPixels, int w, int h, DomaineMath domaineMath, int n, float t);

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

MandelbrotJulia::MandelbrotJulia(unsigned int w, unsigned int h, float dt, int n, float xMin,float xMax,float yMin,float yMax,bool isJulia,float cX,float cY) :
	variateurAnimation(IntervalF(10, 100), dt)
    {
    // Inputs
    this->w = w;
    this->h = h;
    this->n = n;
    this->cX=cX;
    this->cY=cY;
    this->isJulia=isJulia;

    // Tools
    this->dg = dim3(8, 8, 1); // disons a optimiser
    this->db = dim3(16, 16, 1); // disons a optimiser
    this->t = 0;
    ptrDomaineMathInit=new DomaineMath(xMin,yMin,xMax,yMax);

    //Outputs
    this->title = "MandelbrotJulia  CUDA";

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
    this->t = variateurAnimation.varierAndGet(); // in [0,2pi]
    }

/**
 * Override
 */
void MandelbrotJulia::runGPU(uchar4* ptrDevPixels, const DomaineMath& domaineMath)
    {
    mandelbrotJulia<<<dg,db>>>(ptrDevPixels,w,h,domaineMath,t,cX,cY,isJulia);
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

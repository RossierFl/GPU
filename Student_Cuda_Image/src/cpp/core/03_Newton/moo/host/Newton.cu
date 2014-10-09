#include <assert.h>

#include "Newton.h"
#include "Device.h"
#include "MathTools.h"
#include <stdio.h>

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Imported	 	*|
 \*-------------------------------------*/

__global__ void fractaleNewton(uchar4* ptrDevPixels, int w, int h, DomaineMath domaineMath, int n, float t,
	float epsilonx, float* jacobiMatrix);

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

Newton::Newton(int w, int h, float dt, int n, float epsilonx,
	double c1, double c2, double x1, double y1, double x2, double y2) :
		variateurAnimation(IntervalF(30, 100), dt)
    {
    // Inputs
    this->w = w;
    this->h = h;
    this->n = n;

    this->c1 = c1;
    this->c2 = c2;

    this->epsilonx = epsilonx;

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
    this->t = variateurAnimation.varierAndGet(); // in [30,100]
    }

/**
 * Override
 */
void Newton::runGPU(uchar4* ptrDevPixels, const DomaineMath& domaineMath)
    {
    float* jacobiMatrix;
    cudaMalloc((void**)&jacobiMatrix,4*sizeof(jacobiMatrix[0]));
    fractaleNewton<<<dg,db>>>(ptrDevPixels,w,h,domaineMath,n,t,epsilonx,jacobiMatrix);
    cudaFree(jacobiMatrix);
    //cudaDeviceSynchronize();
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


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

__global__ void fractaleNewton(uchar4* ptrDevPixels, int w, int h, DomaineMath domaineMath, float t,
	float eX, float eF, float eX_Star,float* jacobianMat);

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

Newton::Newton(int w, int h, float dt, double x1, double y1, double x2, double y2, float eX, float eF, float eX_Star) :
		variateurAnimation(IntervalF(0, 50), dt)
    {
    // Inputs
    this->w = w;
    this->h = h;

    this->eX = eX;
    this->eF = eF;
    this->eX_Star = eX_Star;

    // Tools
    this->dg = dim3(8, 8, 1); // disons a optimiser
    this->db = dim3(16, 16, 1); // disons a optimiser
    this->t = variateurAnimation.varierAndGet();
    ptrDomaineMathInit=new DomaineMath(x1,y1,x2,y2);

    //Outputs
    this->title = "[API Image Fonctionelle] : Newton zoomable CUDA -- Emmanuel Dafflon";

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
    this->t = variateurAnimation.varierAndGet();
    }

/**
 * Override
 */
void Newton::runGPU(uchar4* ptrDevPixels, const DomaineMath& domaineMath)
    {
    float* jacobianMat = NULL; //create pointer
    HANDLE_ERROR(cudaMalloc(&jacobianMat,4*sizeof(float)));//malloc 4 floats
	HANDLE_ERROR(cudaMemset(jacobianMat,0,4*sizeof(float)));//fill with 0
    fractaleNewton<<<dg,db>>>(ptrDevPixels,w,h,domaineMath,t,eX,eF,eX_Star,jacobianMat);//call the fractal function
    cudaFree(jacobianMat);//free mat
    //cudaDeviceSynchronize(); // in case of issues 
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

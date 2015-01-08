
#include "Raytracing.h"

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

extern __global__ void raytracingKernel(uchar4* ptrDevPixels,int w, int h,float t);

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
Raytracing::Raytracing(int w, int h)
    {
    // Inputs
    this->w = w;
    this->h = h;

    this->t = 0;
    }

Raytracing::~Raytracing()
    {

    }

/*-------------------------*\
|*	Methode	           *|
\*-------------------------*/

void Raytracing::animationStep()
    {
    this->t = variateurAnimation.varierAndGet(); // in [30,100]
    }

/**
 * Override
 */
void Raytracing::runGPU(uchar4* ptrDevPixels)
    {
    raytracingKernel<<<dg,db>>>(ptrDevPixels,w,h,t);
    }

/*-------------------------*\
|*	Get	           *|
\*-------------------------*/

/**
 * Override
 */
float Raytracing::getT(void)
    {
    return t;
    }

/**
 * Override
 */
int Raytracing::getW(void)
    {
    return w;
    }

/**
 * Override
 */
int Raytracing::getH(void)
    {
    return h;
    }

/**
 * Override
 */
string Raytracing::getTitle(void)
    {
    return title;
    }

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/


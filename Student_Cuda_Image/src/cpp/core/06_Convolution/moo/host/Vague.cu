#include <iostream>
#include <assert.h>

#include "Convolution.h"
#include "Device.h"
#include "MathTools.h"

using std::cout;
using std::endl;

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Imported	 	*|
 \*-------------------------------------*/

extern __global__ void convolution(uchar4* ptrDevPixels,int w, int h,float t);

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

Convolution::Convolution(int w, int h,float dt)
    {
    // Inputs
    this->w = w;
    this->h = h;
    this->dt=dt;

    // Tools
    this->dg = dim3(8, 8, 1); // disons a optimiser
    this->db = dim3(16, 16, 1); // disons a optimiser
    this->t=0;

    //Outputs
    this->title="[API Image Cuda] : Convolution CUDA";

    // Check:
    //print(dg, db);
    Device::assertDim(dg, db);
    assert(w== h);

    cout << endl<<"[CBI] Convolution dt =" << dt;
    }

Convolution::~Convolution()
    {
    // rien
    }

/*-------------------------*\
 |*	Methode		    *|
 \*-------------------------*/

/**
 * Override
 * Call periodicly by the API
 */
void Convolution::animationStep()
    {
    t+=dt;
    }

/**
 * Override
 */
void Convolution::runGPU(uchar4* ptrDevPixels)
    {
    rippling<<<dg,db>>>(ptrDevPixels,w,h,t);
    }

/*--------------*\
 |*	get	 *|
 \*--------------*/

/**
 * Override
 */
float Convolution::getT(void)
    {
    return t;
    }

/**
 * Override
 */
int Convolution::getW(void)
    {
    return w;
    }

/**
 * Override
 */
int Convolution::getH(void)
    {
    return  h;
    }

/**
 * Override
 */
string Convolution::getTitle(void)
    {
    return title;
    }

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/


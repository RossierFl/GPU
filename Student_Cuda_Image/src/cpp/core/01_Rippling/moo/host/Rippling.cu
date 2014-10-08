#include <iostream>
#include <assert.h>

#include "Rippling.h"
#include "Device.h"

using std::cout;
using std::endl;

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Imported	 	*|
 \*-------------------------------------*/

extern __global__ void rippling(uchar4* ptrDevPixels, int w, int h, float t);

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

MandelbrotJulia::MandelbrotJulia(int w, int h, float dt)
    {
    assert(w == h);

    // Inputs
    this->w = w;
    this->h = h;
    this->dt = dt;

    // Tools
    this->dg =  dim3(8,8,1);// TODO
    this->db =  dim3(16,16,1); // TODO
    this->t = 0;

    // Outputs
    this->title = "Rippling Cuda";

    //print(dg, db);
    Device::assertDim(dg, db);
    }

MandelbrotJulia::~MandelbrotJulia()
    {
    // rien
    }

/*-------------------------*\
 |*	Methode		    *|
 \*-------------------------*/

/**
 * Override
 */
void MandelbrotJulia::animationStep()
    {
    // TODO
     t+=dt;
    }

/**
 * Override
 */
void MandelbrotJulia::runGPU(uchar4* ptrDevPixels)
    {
    // TODO lancer le kernel avec <<<dg,db>>>
    rippling<<<dg,db>>>(ptrDevPixels,w,h,t);
    }

/*--------------*\
 |*	get	 *|
 \*--------------*/

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


#include <iostream>
#include <assert.h>

#include "HeatTransfert.h"
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

extern __global__ void heatTransfert(uchar4* ptrDevPixels,int w, int h,float t);

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

HeatTransfert::HeatTransfert(int w, int h,float dt)
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
    this->title="[API Image Cuda] : HeatTransfert CUDA";

    // Check:
    //print(dg, db);
    Device::assertDim(dg, db);
    assert(w== h);

    cout << endl<<"[CBI] HeatTransfert dt =" << dt;
    }

HeatTransfert::~HeatTransfert()
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
void HeatTransfert::animationStep()
    {
    t+=dt;
    }

/**
 * Override
 */
void HeatTransfert::runGPU(uchar4* ptrDevPixels)
    {
    heatTransfert<<<dg,db>>>(ptrDevPixels,w,h,t);
    }

/*--------------*\
 |*	get	 *|
 \*--------------*/

/**
 * Override
 */
float HeatTransfert::getT(void)
    {
    return t;
    }

/**
 * Override
 */
int HeatTransfert::getW(void)
    {
    return w;
    }

/**
 * Override
 */
int HeatTransfert::getH(void)
    {
    return  h;
    }

/**
 * Override
 */
string HeatTransfert::getTitle(void)
    {
    return title;
    }

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/


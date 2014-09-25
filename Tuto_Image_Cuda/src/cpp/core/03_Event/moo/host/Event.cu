#include <iostream>
#include <assert.h>

#include "Event.h"
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

extern __global__ void event(uchar4* ptrDevPixels,int w, int h,DomaineMath domaineMath,float t);

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

Event::Event(int w, int h, float dt)
    {
    // Inputs
    this->w = w;
    this->h = h;

    // Tools
    this->dg = dim3(8, 8, 1); // disons a optimiser
    this->db = dim3(16, 16, 1); // disons a optimiser
    this->t = 0;
    ptrDomaineMathInit = new DomaineMath(0, 0, 10, 10);

    //Outputs
    this->title = "[API Image Cuda] : Event Window, try to clik on the window, and look console";

    // Check:
    //print(dg, db);
    Device::assertDim(dg, db);

    }

Event::~Event()
    {
    // rien
    }

/*-------------------------*\
 |*	Methode		    *|
 \*-------------------------*/

/**
 * Override
 */
void Event::animationStep()
    {
    // rien
    }

/**
 * Override
 */
void Event::runGPU(uchar4* ptrDevPixels, const DomaineMath& domaineMath)
    {
    event<<<dg,db>>>(ptrDevPixels,w,h,domaineMath,t);
    }

/*--------------*\
 |*	get	 *|
 \*--------------*/


/**
 * Override
 */
DomaineMath* Event::getDomaineMathInit(void)
    {
    return ptrDomaineMathInit;
    }

/**
 * Override
 */
float Event::getT(void)
    {
    return t;
    }

/**
 * Override
 */
int Event::getW(void)
    {
    return w;
    }

/**
 * Override
 */
int Event::getH(void)
    {
    return h;
    }

/**
 * Override
 */
string Event::getTitle(void)
    {
    return title;
    }


/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/


#include <assert.h>

#include "MandelbrotJuliaMultiGPU.h"
#include "Device.h"
#include "MathTools.h"

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Imported	 	*|
 \*-------------------------------------*/

__global__ void mandelbrotJuliaCuMltiGPU(uchar4* ptrDevPixels,int w, int h,DomaineMath domaineMath, int n,float t,bool isJulia,float cX,float cY,float offset);

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

MandelbrotJuliaMultiGPU::MandelbrotJuliaMultiGPU(int w, int h, float dt, int n,float xMin,float xMax,float yMin,float yMax,bool isJulia,float cX=0,float cY=0) :
	variateurAnimation(IntervalF(20, 200),dt)
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
    this->title = "[API Image Fonctionelle] : MandelbrotJuliaMultiGPU zoomable CUDA";

    // Check:
    //print(dg, db);
    Device::assertDim(dg, db);
    assert(w == h);
    }

MandelbrotJuliaMultiGPU::~MandelbrotJuliaMultiGPU()
    {
   delete ptrDomaineMathInit;
    }

/*-------------------------*\
 |*	Methode		    *|
 \*-------------------------*/

/**
 * Override
 */
void MandelbrotJuliaMultiGPU::animationStep()
    {
    this->t = variateurAnimation.varierAndGet(); // in [0,2pi]
    }

/**
 * Override
 */
void MandelbrotJuliaMultiGPU::runGPU(uchar4* ptrDevPixels, const DomaineMath& domaineMath)
    {
   // cudaSetDevice(1);
   // cudaSetDevice(0);
   // double x0 =domaineMath.x0;
   // double y0 =domaineMath.y0;
   // double x1 =domaineMath.x1;
    //double y1 =domaineMath.y1;
    //double dx = (x1-x0)/6;
    //double dy = (y1-y0)/6;


    //DomaineMath dm(x0,y0,x0+dx,y0+dy);

    mandelbrotJuliaCuMltiGPU<<<dg,db>>>(ptrDevPixels,w,h/6,domaineMath,n,t, isJulia, cX, cY,0);
    mandelbrotJuliaCuMltiGPU<<<dg,db>>>(ptrDevPixels,w,h/6*2,domaineMath,n,t, isJulia, cX, cY,h/6);
    mandelbrotJuliaCuMltiGPU<<<dg,db>>>(ptrDevPixels,w,h/6,domaineMath,n,t, isJulia, cX, cY,h/6*2);
    mandelbrotJuliaCuMltiGPU<<<dg,db>>>(ptrDevPixels,w,h/6,domaineMath,n,t, isJulia, cX, cY,h/6*3);
    mandelbrotJuliaCuMltiGPU<<<dg,db>>>(ptrDevPixels,w,h/6,domaineMath,n,t, isJulia, cX, cY,h/6*4);
    mandelbrotJuliaCuMltiGPU<<<dg,db>>>(ptrDevPixels,w,h/6,domaineMath,n,t, isJulia, cX, cY,h/6*5);
    }

/*--------------*\
 |*	get	 *|,
 \*--------------*/

/**
 * Override
 */
DomaineMath* MandelbrotJuliaMultiGPU::getDomaineMathInit(void)
    {
    return ptrDomaineMathInit;
    }

/**
 * Override
 */
float MandelbrotJuliaMultiGPU::getT(void)
    {
    return t;
    }

/**
 * Override
 */
int MandelbrotJuliaMultiGPU::getW(void)
    {
    return w;
    }

/**
 * Override
 */
int MandelbrotJuliaMultiGPU::getH(void)
    {
    return h;
    }

/**
 * Override
 */
string MandelbrotJuliaMultiGPU::getTitle(void)
    {
    return title;
    }

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/


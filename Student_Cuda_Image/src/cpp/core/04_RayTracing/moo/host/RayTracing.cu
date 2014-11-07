#include <assert.h>

#include "RayTracing.h"
#include "Device.h"
#include "MathTools.h"
#include <stdio.h>

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Imported	 	*|
 \*-------------------------------------*/

__global__ void rayTracing(uchar4* ptrDevPixels, int w, int h, float t, Sphere* spheres, int n);

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

RayTracing::RayTracing(int w, int h, float dt, double x1, double y1, double x2, double y2, Sphere* spheres, int n) :
		variateurAnimation(IntervalF(0,10), dt)
    {
    // Inputs
    this->w = w;
    this->h = h;
	
    this->spheres = spheres;
    this->n = n;
	
    // Tools
    this->dg = dim3(8, 8, 1); // disons a optimiser
    this->db = dim3(16, 16, 1); // disons a optimiser
    this->t = variateurAnimation.varierAndGet();

    //Outputs
    this->title = "[API Image Normale] : RayTracing non-zoomable CUDA -- Emmanuel Dafflon";

    // Check:
    //print(dg, db);
    Device::assertDim(dg, db);
    assert(w == h);
    }

RayTracing::~RayTracing()
    {
    }

/*-------------------------*\
 |*	Methode		    *|
 \*-------------------------*/

/**
 * Override
 */
void RayTracing::animationStep()
    {
    this->t = variateurAnimation.varierAndGet();
    }

/**
 * Override
 */
void RayTracing::runGPU(uchar4* ptrDevPixels)
    {
    Sphere* spheresToDev = NULL; //create pointer
    HANDLE_ERROR(cudaMalloc(&spheresToDev,n*sizeof(Sphere)));//malloc all spheres
    HANDLE_ERROR(cudaMemcpy(spheresToDev,spheres,n*sizeof(Sphere),cudaMemcpyHostToDevice));//fill with spheres
    rayTracing<<<dg,db>>>(ptrDevPixels,w,h,t,spheresToDev,n);//call
    cudaFree(spheresToDev);//free mat
    cudaDeviceSynchronize(); // in case of issues
    //printf("\n");
    //exit(0);
    //get fps to do smooth animation ??
    }

/*--------------*\
 |*	get	 *|
 \*--------------*/

/**
 * Override
 */
float RayTracing::getT(void)
    {
    return t;
    }

/**
 * Override
 */
int RayTracing::getW(void)
    {
    return w;
    }

/**
 * Override
 */
int RayTracing::getH(void)
    {
    return h;
    }

/**
 * Override
 */
string RayTracing::getTitle(void)
    {
    return title;
    }

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/

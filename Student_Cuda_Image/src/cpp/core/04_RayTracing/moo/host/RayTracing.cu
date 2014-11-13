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

__global__ void rayTracing(uchar4* ptrDevPixels, int w, int h, float t, Sphere* ptrSpheresDevGM, int n);

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
		variateurAnimation(IntervalF(0, 15), dt)
{
	// Check
	assert(w == h);

	// Inputs
	this->w = w;
	this->h = h;
	this->spheres = spheres;
	this->n = n;

	// Tools
	this->dg = dim3(8, 8, 1); // disons, à optimiser
	this->db = dim3(16, 16, 1); // disons, à optimiser
	this->t = variateurAnimation.varierAndGet();

	Device::assertDim(dg, db);
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
	/* Pointer on global memory for the spheres */
	Sphere* ptrSpheresDevGM = NULL;

	/* Allocate in global memory */
	HANDLE_ERROR(cudaMalloc(&ptrSpheresDevGM, n * sizeof(Sphere)));

	/* Copy from RAM to GRAM */
	HANDLE_ERROR(cudaMemcpy(ptrSpheresDevGM, spheres, n * sizeof(Sphere), cudaMemcpyHostToDevice));

	/* Launch kernel */
	// @formatter:off
	rayTracing<<<dg,db>>>(ptrDevPixels, w, h, t, ptrSpheresDevGM, n);
	// @formatter:on

	/* Free memory */
	cudaFree(ptrSpheresDevGM);

	/* DEBUG */
	cudaDeviceSynchronize();
	printf("\n");
}

/*--------------*\
 |*	get	 *|
 \*--------------*/

/**
* Override
*/
float RayTracing::getT()
{
	return t;
}

/**
* Override
*/
int RayTracing::getW()
{
	return w;
}

/**
* Override
*/
int RayTracing::getH()
{
	return h;
}

/**
* Override
*/
string RayTracing::getTitle()
{
	return "Ray tracing";
}

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/

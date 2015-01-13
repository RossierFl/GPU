
#include "Raytracing.h"

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

extern __global__ void raytracingKernel(uchar4* ptrDevPixels, int w, int h, float t, Sphere* spheres, int n);

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
Raytracing::Raytracing(int w, int h, Sphere* spheres, int n)
    {
    // Inputs
    this->w = w;
    this->h = h;

    this->t = 0;

    this->spheres = spheres;
    this->n = n;
    // Tools
    this->dg = dim3(8, 8, 1); // TODO disons a optimiser
    this->db = dim3(16, 16, 1); // TODO disons a optimiser
    this->t = variateurAnimation.varierAndGet();
    //Outputs
    this->title = "RayTracing non-zoomable CUDA";
    // control
    Device::assertDim(dg, db);
    assert(w == h);
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
    Sphere* spheresDevGRAM = NULL;
    HANDLE_ERROR(cudaMalloc(&spheresDevGRAM, n * sizeof(Sphere)));
    HANDLE_ERROR(cudaMemcpy(spheresDevGRAM, spheres, n * sizeof(Sphere), cudaMemcpyHostToDevice));
    raytracingKernel<<<dg,db>>>(ptrDevPixels, w, h, t, spheresDevGRAM, n);
    cudaFree(spheresDevGRAM);
    cudaDeviceSynchronize();
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


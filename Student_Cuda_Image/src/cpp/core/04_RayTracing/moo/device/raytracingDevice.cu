
#include "Sphere.h"
#include "Indice2D.h"
#include "IndiceTools.h"
#include "RaytracingMath.h"

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/
__global__ void raytracingKernel(uchar4* ptrDevPixels, int w, int h, float t, Sphere* spheres, int n);

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

/*----------------------------------------------------------------------*\
 |*			Implementation 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/
__global__ void raytracingKernel(uchar4* ptrDevPixels, int w, int h, float t, Sphere* spheres, int n)
    {
    const int TID = Indice2D::tid();
    const int NB_THREAD = Indice2D::nbThread();
    const int WH = w * h;

    RayTracingMath* math = new RayTracingMath();

    int s = TID;

    uchar4 color;
    int x;
    int y;

    while (s < WH) {
	IndiceTools::toIJ(s, w, &x, &y);
	math->colorXY(&color, x, y, t, spheres, n);
	ptrDevPixels[s] = color;
	s += NB_THREAD;
    }

    delete math;

    }

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/


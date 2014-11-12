#include "Indice2D.h"
#include "IndiceTools.h"
#include "DomaineMath.h"
#include "cudaTools.h"
#include "Device.h"
#include "RayTracingMath.h"
#include "Sphere.h"

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Imported	 	*|
 \*-------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

__global__ void rayTracing(uchar4* ptrDevPixels, int w, int h, DomaineMath domaineMath, float t, Sphere* ptrSpheresDevGM, int n);

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/



/*----------------------------------------------------------------------*\
 |*			Implementation 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

__global__ void rayTracing(uchar4* ptrDevPixels, int w, int h, float t, Sphere* ptrSpheresDevGM, int n)
{
	RayTracingMath* math = new RayTracingMath();

	const int TID = Indice2D::tid();
	const int NB_THREAD = Indice2D::nbThread();
	const int WH = w * h;

	uchar4 color;
	int x;
	int y;

	int s = TID;
	while (s < WH)
	{
		IndiceTools::toIJ(s, w, &x, &y);
		math->colorXY(&color, x, y, t, ptrSpheresDevGM, n);
		ptrDevPixels[s] = color;
		s += NB_THREAD;
	}

	delete math;
}

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/

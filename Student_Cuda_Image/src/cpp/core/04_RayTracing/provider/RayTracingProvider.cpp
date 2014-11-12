#include "RayTracingProvider.h"
#include "MathTools.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
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

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

/*----------------------------------------------------------------------*\
 |*			Implementation 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

/*-----------------*\
 |*	static	   *|
 \*----------------*/

RayTracing* RayTracingProvider::create()
{
	int dw = 16 * 60;
	int dh = 16 * 60;
	float dt = 0.001f;

	int nbBalls = 50;

	double x1 = 0;
	double x2 = x1 + dw;
	double y1 = 0;
	double y2 = y1 + dh;
	double z1 = 10;
	double z2 = x2 * 2;

	srand48(time(NULL));

	Sphere* spheres = (Sphere*) malloc(sizeof(Sphere) * nbBalls);
	for (int i = 0; i < nbBalls; i++)
	{
		float x = x1 + drand48() * (x2 - x1);
		float y = y1 + drand48() * (y2 - y1);
		float z = z1 + drand48() * (z2 - z1);
		float r = 20 + drand48() * (x2 / 10);
		float hue = drand48();

		float3 centre;
		centre.x = x;
		centre.y = y;
		centre.z = z;

		spheres[i] = Sphere(centre, r, hue);
	}

	return new RayTracing(dw, dh, dt, x1, y1, x2, y2, spheres, nbBalls);
}

Image* RayTracingProvider::createGL()
{
	return new Image(create());
}

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/

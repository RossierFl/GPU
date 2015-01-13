#include "RaytracingProvider.h"
#include "MathTools.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

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

Raytracing* RaytracingProvider::create() {
	int dw = 16 * 60;
	int dh = 16 * 60;

	int nBall = 50;

	double x1 = 0;
	double x2 = dw;
	double y1 = 0;
	double y2 = dh;
	double z1 = 10;
	double z2 = x2 * 2;

	float maxRBall = x2 / 10.0;

	srand48 (time(NULL));

	Sphere* spheres = NULL;
	spheres = (Sphere*) malloc(sizeof(Sphere) * nBall);
	for (int i = 0; i < nBall; i++) {
		float x = drand48();
		float y = drand48();
		float z = drand48();
		float r = drand48();
		float hue = drand48();

		float3 centre;
		centre.x = x1 + x * (x2 - x1);
		centre.y = y1 + y * (y2 - y1);
		centre.z = z1 + z * (z2 - z1);

		spheres[i] = Sphere(centre, 20 + r * maxRBall, hue);
	}
	float dt = 0.001f;
	return new Raytracing(dw, dh, spheres, nBall);
}

Image* RaytracingProvider::createGL(void) {
	return new Image(create());
}

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/


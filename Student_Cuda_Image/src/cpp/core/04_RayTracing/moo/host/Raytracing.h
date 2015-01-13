#ifndef RAYTRACING_H_
#define RAYTRACING_H_

#include <assert.h>

#include "cudaTools.h"
#include "Animable_I.h"
#include "MathTools.h"
#include "VariateurF.h"
#include "Device.h"
#include "Sphere.h"

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

class Raytracing: public Animable_I
    {

    public:

	Raytracing(int w, int h, Sphere* spheres, int n);
	virtual ~Raytracing(void);

    public:

	virtual void animationStep(void);
	void runGPU(uchar4* ptrDevPixels); // Override

	float getT(void); // Override
	int getW(void); // Override
	int getH(void); // Override
	string getTitle(void); // Override

    private:

	// Inputs
	int w;
	int h;

	// Tools
	dim3 dg;
	dim3 db;
	float t; // para animation
	VariateurF variateurAnimation; // varier t

	//Outputs
	string title;

	Sphere* spheres;
	int n;
    };

#endif 

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/

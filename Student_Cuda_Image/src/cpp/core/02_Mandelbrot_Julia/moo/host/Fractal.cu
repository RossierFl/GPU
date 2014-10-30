#include <iostream>
#include <assert.h>
#include "MathTools.h"
#include "Fractal.h"
#include "Device.h"

using std::cout;
using std::endl;

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Imported	 	*|
 \*-------------------------------------*/

extern __global__ void fractalGPU(uchar4* ptrDevPixels, int w, int h, int n, DomaineMath domaineMath);

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

Fractal::Fractal(int w, int h, float dt, int n, double x1, double y1, double x2, double y2) :
		variateur(IntervalF(30, 100), dt) {

	// Inputs
	this->w = w;
	this->h = h;
	this->n = n;
	this->domaineMath = new DomaineMath(x1, y1, x2, y2);
	this->t = 0;

	// Tools
	this->dg = dim3(8, 8, 1);
	this->db = dim3(16, 16, 1);
	Device::checkDimError(dg, db);
	Device::checkDimOptimiser(dg, db);

	// Outputs
	this->title = "Fractal Cuda";

	//print(dg, db);
	Device::assertDim(dg, db);
	assert(w == h);
}

Fractal::~Fractal() {
	delete domaineMath;
}

/*-------------------------*\
 |*	Methode		    *|
 \*-------------------------*/

/**
 * Override
 */
void Fractal::animationStep() {
	t = variateur.varierAndGet();
}

/**
 * Override
 */
void Fractal::runGPU(uchar4* ptrDevPixels, const DomaineMath& domaineMath) {
	fractalGPU<<<dg,db>>>(ptrDevPixels, w, h, n, domaineMath);
	//Device::synchronize();
	//Device::checkKernelError("Error>> Fractal::runGPU");
}

/*--------------*\
 |*	get	 *|
 \*--------------*/

float Fractal::getT(void) {
	return t;
}

int Fractal::getW(void) {
	return w;
}

int Fractal::getH(void) {
	return h;
}

DomaineMath* Fractal::getDomaineMathInit() {
	return domaineMath;
}

string Fractal::getTitle(void) {
	return title;
}

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/


#include <iostream>
#include <assert.h>

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

extern __global__ void fractal_gpu(uchar4* ptrDevPixels, int w, int h, int n, DomaineMath& domaineMath);

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

Fractal::Fractal(int w, int h, float dt, int n, float x1, float y1, float x2, float y2) :
		variateur(IntervalI(30, 100), dt) {

	// Inputs
	this->w = w;
	this->h = h;
	this->n = n;
	this->x1 = x1;
	this->y1 = y1;
	this->x2 = x2;
	this->y2 = y2;
	this->domaineMath = new DomaineMath(x1, y1, x2, y2);

	// Tools
	this->dg = dim3(16, 16, 1);
	this->db = dim3(8, 8, 1);

	// Outputs
	this->title = "Fractal Cuda";

	//print(dg, db);
	Device::assertDim(dg, db);
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
	n = variateur.varierAndGet();
}

/**
 * Override
 */
void Fractal::runGPU(uchar4* ptrDevPixels, DomaineMath& useless) {
	fractal_gpu<<< db, db >>>(ptrDevPixels, w, h, n, useless);
}

/*--------------*\
 |*	get	 *|
 \*--------------*/

float Fractal::getT(void) {
return n;
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


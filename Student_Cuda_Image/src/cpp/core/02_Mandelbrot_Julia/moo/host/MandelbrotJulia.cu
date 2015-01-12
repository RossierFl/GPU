#include <assert.h>

#include "MandelbrotJulia.h"
#include "Device.h"
#include "MathTools.h"
#include <stdio.h>

__global__ void fractale(bool isJulia, uchar4* ptrDevPixels, int w, int h, DomaineMath domaineMath, int n, float t, float c1, float c2);

MandelbrotJulia::MandelbrotJulia(bool isJulia, int w, int h, float dt, int n, float c1, float c2, float x1, float x2, float y1, float y2) :
		variateurAnimation(IntervalF(30, 100), dt) {
	// Inputs
	this->w = w;
	this->h = h;
	this->n = n;

	this->c1 = c1;
	this->c2 = c2;

	this->isJulia = isJulia;

	// Tools
	this->dg = dim3(8, 8, 1); // disons a optimiser
	this->db = dim3(16, 16, 1); // disons a optimiser
	this->t = 0;
	ptrDomaineMathInit = new DomaineMath(x1, y1, x2, y2);

	//Outputs
	this->title = "[API Image Fonctionelle] : Mandelbrot or Julia zoomable";

	Device::assertDim(dg, db);
	assert(w == h);
}

MandelbrotJulia::~MandelbrotJulia() {
	delete ptrDomaineMathInit;
}

/**
 * Override
 */
void MandelbrotJulia::animationStep() {
	this->t = variateurAnimation.varierAndGet();
}

/**
 * Override
 */
void MandelbrotJulia::runGPU(uchar4* ptrDevPixels, const DomaineMath& domaineMath) {
	fractale<<<dg,db>>>(isJulia, ptrDevPixels, w, h, domaineMath, getT(), t, c1, c2);
}

/**
 * Override
 */
DomaineMath* MandelbrotJulia::getDomaineMathInit() {
	return ptrDomaineMathInit;
}

/**
 * Override
 */
float MandelbrotJulia::getT() {
	return t;
}

/**
 * Override
 */
int MandelbrotJulia::getW() {
	return w;
}

/**
 * Override
 */
int MandelbrotJulia::getH() {
	return h;
}

/**
 * Override
 */
string MandelbrotJulia::getTitle() {
	return title;
}

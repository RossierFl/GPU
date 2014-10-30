#include <assert.h>

#include "Newton.h"
#include "Device.h"
#include "MathTools.h"
#include <stdio.h>

/*----------------------------------------------------------------------*\
|*			Declaration 												*|
\*----------------------------------------------------------------------*/

/*--------------------------------------*\
|*		Imported					 	*|
\*--------------------------------------*/

__global__ void fractaleNewton(uchar4* ptrDevPixels, int w, int h, DomaineMath domaineMath, int n, float epsilonx, float epsilonf, float epsilonxstar, float* jacobiMatrix);

/*--------------------------------------*\
|*		Public							*|
\*--------------------------------------*/

/*--------------------------------------*\
|*		Private							*|
\*--------------------------------------*/

/*----------------------------------------------------------------------*\
|*			Implementation 												*|
\*----------------------------------------------------------------------*/

/*-------------------------*\
|*	Constructor		       *|
\*-------------------------*/

Newton::Newton(int w, int h, float dt, int n, float epsilonx, float epsilonf, float epsilonxstar, double x1, double y1, double x2, double y2)
		:
		animationVariator(IntervalF(30, 100), dt)
{
	// Inputs
	this->w = w;
	this->h = h;
	this->n = n;

	this->epsilonx = epsilonx;
	this->epsilonf = epsilonf;
	this->epsilonxstar = epsilonxstar;

	// Tools
	this->dg = dim3(8, 8, 1); // TODO à optimiser
	this->db = dim3(16, 16, 1); // TODO à optimiser
	this->t = 0;
	ptrDomaineMathInit = new DomaineMath(x1, y1, x2, y2);

	Device::assertDim(dg, db);
	assert(w == h);
}

Newton::~Newton()
{
	delete ptrDomaineMathInit;
}

/*------------------------*\
|*	Methods	  			  *|
\*------------------------*/

void Newton::animationStep()
{
	this->t = animationVariator.varierAndGet(); // in [30,100]
}

void Newton::runGPU(uchar4* ptrDevPixels, const DomaineMath& domaineMath)
{
	// Run the computation on the GPU
	// @formatter:off
	fractalNewton<<<dg,db>>>(ptrDevPixels, w, h, domaineMath, n, epsilonx, epsilonf, epsilonxstar);
	// @formatter:on
}

DomaineMath* Newton::getDomaineMathInit()
{
	return ptrDomaineMathInit;
}

float Newton::getT()
{
	return t;
}

int Newton::getW()
{
	return w;
}

int Newton::getH()
{
	return h;
}

std::string Newton::getTitle()
{
	return "Newton";
}



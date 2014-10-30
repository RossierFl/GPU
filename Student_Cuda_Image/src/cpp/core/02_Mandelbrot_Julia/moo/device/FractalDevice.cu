#include <iostream>
#include <stdio.h>

#include "Indice2D.h"
#include "IndiceTools.h"
#include "DomaineMath.h"
#include "cudaTools.h"
#include "Device.h"
#include "FractalMath.h"
#include "FractalMathMandelbrot.h"

using std::cout;
using std::endl;

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Imported	 	*|
 \*-------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

__global__ void fractalGPU(uchar4* ptrDevPixels, int w, int h, int n, DomaineMath domaineMath);

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

__global__ void fractalGPU(uchar4* ptrDevPixels, int w, int h, int n, DomaineMath domaineMath) {
	FractalMath* fractalMath = new FractalMathMandelbrot(n);
	const int TID = Indice2D::tid();
	const int NB_THREAD = Indice2D::nbThread();
	const int WH = w * h;
	int s = TID;
	int i = 0;
	int j = 0;
	double x = 0;
	double y = 0;
	uchar4 color;

	while (s < WH) {
		// job
		IndiceTools::toIJ(s, w, &i, &j);
		domaineMath.toXY(i, j, &x, &y);
		fractalMath->color(x, y, &color);
		ptrDevPixels[s] = color;
		s += NB_THREAD;
	}

	delete fractalMath;
}

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/


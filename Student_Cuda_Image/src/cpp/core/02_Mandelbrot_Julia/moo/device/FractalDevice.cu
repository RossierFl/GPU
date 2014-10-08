#include <iostream>

#include "Indice2D.h"
#include "cudaTools.h"
#include "Device.h"

#include "FractalMath.h"
#include "FractalMathMandelbrot.h"
#include "IndiceTools.h"
#include "DomaineMath.h"

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

__global__ void fractal_gpu(uchar4* ptrDevPixels, int w, int h, int n, DomaineMath& domaineMath);

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

__global__ void fractal_gpu(uchar4* ptrDevPixels, int w, int h, int n, DomaineMath& domaineMath) {
	FractalMath* fractalMath = new FractalMathMandelbrot(n);

	const int TID = Indice2D::tid();
	const int NB_THREAD = Indice2D::nbThread();
	const int WH = w * h;
	int s = TID;
	int i = 0;
	int j = 0;
	double x = 0;
	double y = 0;

	while (s < WH) {
		// job
		IndiceTools::toIJ(s, w, &i, &j);
		domaineMath.toXY(i, j, &x, &y);
		fractalMath->color(x, y, *ptrDevPixels);
		s += NB_THREAD;
	}

	delete fractalMath;
}

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/


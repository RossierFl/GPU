#include "Indice2D.h"
#include "IndiceTools.h"
#include "DomaineMath.h"
#include "cudaTools.h"
#include "Device.h"
#include "FractalMath.h"
#include <stdio.h>



/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Imported	 	*|
 \*-------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/
__global__ void fractal(uchar4* ptrDevPixels, int w, int h, const DomaineMath& domaineMath, int n, double cx, double cyi, bool isJulia);

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

/**
 * Code entrainement Cuda
 */
__global__ void fractal(uchar4* ptrDevPixels, int w, int h, DomaineMath domaineMath, int n, double cx, double cyi, bool isJulia)
    {

    FractalMath fractalMath = FractalMath();

    double x = 0.0;
    double y = 0.0;

    const int TID = Indice2D::tid();
    const int NB_THREADS = Indice2D::nbThread();
    const int SIZE = w*h;
    uchar4 color;
    int s = TID;
    int i =0;
    int j =0;
    while(s<SIZE){
	IndiceTools::toIJ(s, w, &i, &j); // s[0,W*H[ --> i[0,H[ j[0,W[

	domaineMath.toXY(i, j, &x, &y); // fill (x,y) from (i,j)

	if(isJulia)
	    fractalMath.colorXY(&color,x, y, n, cx, cyi, x, y); // in [01]
	else
	    fractalMath.colorXY(&color,x, y, n, x,y, 0,0);
	ptrDevPixels[s]=color;

	s+=NB_THREADS;
    }
    }

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/


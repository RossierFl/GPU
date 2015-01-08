#ifndef MANDELBROTMATH_H_
#define MANDELBROTMATH_H_

#include "Fractale.h"

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

/**
 * Dans un header only pour preparer la version cuda
 */
class MandelbrotMath : public Fractale
    {
	/*--------------------------------------*\
	 |*		Constructeur		*|
	 \*-------------------------------------*/

    public:

	/**
	 * calibreurColor : transformation affine entre [0,N] et [0,1] (le spectre hsb)
	 */
	__device__ MandelbrotMath(int n) : Fractale(n)
	{
	//this->n = n;
	}

	__device__
	virtual ~MandelbrotMath(void)
	    {
	    // rien
	    }

	/*--------------------------------------*\
	|*		Methode			*|
	 \*-------------------------------------*/

    public:

	__device__
	int indiceArret(double x, double y)
	    {
	int k = 0;
	double a = 0.0;
	double b = 0.0;
	while(((a*a)+(b*b))<=4.0 && k <= n )
	    {
	    double aCopy = a;
	    a = ((a*a)-(b*b))+x;
	    b = (2.0*aCopy*b)+y;
	    k++;
	    }
	return k;
	    }

    }
;

#endif 

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/

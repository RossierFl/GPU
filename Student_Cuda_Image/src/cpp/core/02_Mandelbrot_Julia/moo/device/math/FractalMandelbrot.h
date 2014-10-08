#ifndef FRACTAL_MANDELBROT_H_
#define FRACTAL_MANDELBROT_H_

#include "ColorTools.h"
#include <math.h>

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

/**
 * Dans un header only pour preparer la version cuda
 */
class FractalMandelbrot : public FractalMath
    {
	/*--------------------------------------*\
	 |*		Constructeur		*|
	 \*-------------------------------------*/

    public:

	/**
	 * calibreurColor : transformation affine entre [-1,1] (l'output de f(x,y)) et [0,1] (le spectre hsb)
	 */
      __device__ FractalMandelbrot(int n) :FractalMath(n)
		//calibreur(IntervalF(-1, 1), IntervalF(0, 1))
	    {

	    this->n = n;
	    }

      __device__ virtual ~FractalMandelbrot(void)
	    {
	    // rien
	    }

	/*--------------------------------------*\
	|*		Methode			*|
	 \*-------------------------------------*/

    public:

      __device__ void indiceArret(double x, double y,int* ret){
	      double a = 0.0;
	      double b = 0.0;
	      *ret = 0;
	      while(*ret<n&&a*a+b*b<4){
		  double ca = a;
		  a = (a*a-b*b)+x;
		  b = 2*ca*b+y;
		  *ret++;
	      }
	}

	/*--------------------------------------*\
	|*		Attribut		*|
	 \*-------------------------------------*/

    protected:

	// Inputs
	int n;

    }
;

#endif 

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/

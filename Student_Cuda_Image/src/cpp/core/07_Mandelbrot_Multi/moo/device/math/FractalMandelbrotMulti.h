#ifndef FRACTAL_MANDELBROT_MULTI_H_
#define FRACTAL_MANDELBROT_MULTI_H_

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
class FractalMandelbrotMulti : public FractalMathMulti
    {
	/*--------------------------------------*\
	 |*		Constructeur		*|
	 \*-------------------------------------*/

    public:

	/**
	 * calibreurColor : transformation affine entre [-1,1] (l'output de f(x,y)) et [0,1] (le spectre hsb)
	 */
      __device__ FractalMandelbrotMulti(int n) :FractalMathMulti(n)
		//calibreur(IntervalF(-1, 1), IntervalF(0, 1))
	    {

	    this->n = n;
	    }

      __device__ virtual ~FractalMandelbrotMulti(void)
	    {
	    // rien
	    }

	/*--------------------------------------*\
	|*		Methode			*|
	 \*-------------------------------------*/

    public:

      __device__ int indiceArret(double x, double y, int t){
	      double a = 0.0;
	      double b = 0.0;
	      int ret = 0;
	      while(ret<t&&a*a+b*b<4){
		  double ca = a;
		  a = (a*a-b*b)+x;
		  b = 2*ca*b+y;
		  ret++;
	      }
	      return ret;
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

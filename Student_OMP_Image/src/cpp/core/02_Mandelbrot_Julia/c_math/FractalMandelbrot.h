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
class FractalMandelbrot : public Fractal
    {
	/*--------------------------------------*\
	 |*		Constructeur		*|
	 \*-------------------------------------*/

    public:

	/**
	 * calibreurColor : transformation affine entre [-1,1] (l'output de f(x,y)) et [0,1] (le spectre hsb)
	 */
      FractalMandelbrot(int n) :Fractal(n)
		//calibreur(IntervalF(-1, 1), IntervalF(0, 1))
	    {

	    this->n = n;
	    }

	virtual ~FractalMandelbrot(void)
	    {
	    // rien
	    }

	/*--------------------------------------*\
	|*		Methode			*|
	 \*-------------------------------------*/

    public:

	int indiceArret(double x, double y){
	      double a = 0.0;
	      double b = 0.0;
	      int k = 0;
	      while(k<n&&a*a+b*b<4){
		  double ca = a;
		  a = (a*a-b*b)+x;
		  b = 2*ca*b+y;
		  k++;
	      }
	      return k;
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

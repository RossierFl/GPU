#ifndef FRACTAL_JULIA_H_
#define FRACTAL_JULIA_H_

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
class FractalJulia : public FractalMath
    {
	/*--------------------------------------*\
	 |*		Constructeur		*|
	 \*-------------------------------------*/

    public:

	/**
	 * calibreurColor : transformation affine entre [-1,1] (l'output de f(x,y)) et [0,1] (le spectre hsb)
	 */
  __device__ FractalJulia(int n,double cx,double cy):FractalMath(n)
		//calibreur(IntervalF(-1, 1), IntervalF(0, 1))
	    {
	    this->n = n;
	    this->cx = cx;
	    this->cy = cy;
	    }

  __device__ ~FractalJulia(void)
	    {
	    // rien
	    }

	//virtual int indiceArret(double x, double y);

	/*--------------------------------------*\
	|*		Methode			*|
	 \*-------------------------------------*/

    public:

  __device__ void indiceArret(double x, double y,int* ret){
	  double a = x;
	  double b = y;
	  *ret = 0;
	  while(*ret<n&&a*a+b*b<4){
	      double ca = a;
	      a = (a*a-b*b)+this->cx;
	      b = 2*ca*b+this->cy;
	      *ret++;
	  }
	}

	/*--------------------------------------*\
	|*		Attribut		*|
	 \*-------------------------------------*/

    protected:

	// Inputs
	int n;
	double cx;
	double cy;

    }
;

#endif 

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/

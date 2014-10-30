#ifndef FractalMathMandelbrot_H_
#define FractalMathMandelbrot_H_

#include "FractalMath.h"

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

class FractalMathMandelbrot: public FractalMath {

	public:

		__device__ FractalMathMandelbrot(int n) :
				FractalMath(n) {
		}

		__device__  virtual ~FractalMathMandelbrot() {

		}

		__device__
		int indiceArret(double x, double y) {
			int k = 0;
			double a = 0.0;
			double b = 0.0;
			while (((a * a) + (b * b)) <= 4.0 && k <= n) {
				double aCopy = a;
				a = ((a * a) - (b * b)) + x;
				b = (2.0 * aCopy * b) + y;
				k++;
			}
			return k;
		}
};

#endif

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

		__device__ FractalMathMandelbrot(int n): FractalMath(n) {
		}

		__device__ virtual ~FractalMathMandelbrot() {

		}

		__device__ virtual int indiceArret(double x, double y) {
			double a = 0;
			double b = 0;
			double aCopy = 0;
			double k = 0;

			while((k < n) && (a * a + b * b < 4)) {
				aCopy = a;
				a = (a * a - b * b) + x;
				b = 2 * aCopy * b + y;
				k++;
			}

			return k;
		}
};

#endif

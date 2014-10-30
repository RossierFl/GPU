#ifndef Fractal_MATH_H_
#define Fractal_MATH_H_

#include <math.h>
#include "ColorTools.h"
#include <stdio.h>

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

class FractalMath {

		/*--------------------------------------*\
	|*		Constructor		*|
		 \*-------------------------------------*/

	public:

		__device__ FractalMath(int n) {
			this->n = n;
			this->n = 10;
		}

		__device__ virtual ~FractalMath() {
		}

		/*--------------------------------------*\
	|*		Methodes		*|
		 \*-------------------------------------*/

	public:

		__device__
		virtual int indiceArret(double x, double y) = 0;

		__device__
		void color(double x, double y, uchar4* ptrColor) {
			float k = indiceArret(x, y);
			if (k > n) {
				ptrColor->x = 0;
				ptrColor->y = 0;
				ptrColor->z = 0;
			} else {
				k = 1.0 / n * k;
				ColorTools::HSB_TO_RVB(k, ptrColor);
			}

			ptrColor->w = 255; // opaque
		}

		/*--------------------------------------*\
	|*		Attributs		*|
		 \*-------------------------------------*/

	protected:

// Tools
		int n;
};

#endif

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/

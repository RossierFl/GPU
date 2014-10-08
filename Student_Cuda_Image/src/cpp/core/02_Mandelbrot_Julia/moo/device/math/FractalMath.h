#ifndef Fractal_MATH_H_
#define Fractal_MATH_H_

#include <math.h>
#include "ColorTools.h"

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
		}

		__device__ virtual ~FractalMath() {
		}

		/*--------------------------------------*\
	|*		Methodes		*|
		 \*-------------------------------------*/

	public:

		/**
		 * x=pixelI
		 * y=pixelJ
		 */
		__device__ void color(double x, double y, uchar4& color) {
			int k = this->indiceArret(x, y);

			if(k > n) {
				color.x = 0;
				color.y = 0;
				color.z = 0;
				color.w = 255;
			} else {
				float h = 1.0 / n;
				ColorTools::HSB_TO_RVB(h, &color);
				color.w = 255;
			}
		}

	private:


		__device__ virtual int indiceArret(double x, double y) = 0;

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

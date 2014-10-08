#ifndef RIPPLING_MATH_H_
#define RIPPLING_MATH_H_

#include <math.h>

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

class RipplingMath {

		/*--------------------------------------*\
	|*		Constructor		*|
		 \*-------------------------------------*/

	public:

		__device__ RipplingMath(int w, int h) {
			this->dim2 = w / 2;
		}

		__device__ RipplingMath(const RipplingMath& source) {
			this->dim2 = source.dim2;
		}

		/*--------------------------------------*\
	|*		Methodes		*|
		 \*-------------------------------------*/

	public:

		/**
		 * x=pixelI
		 * y=pixelJ
		 */
		__device__
		void color(int i, int j, float t, uchar4& color) {
			float dxyResult;
			dxy(i, j, &dxyResult);

			double sup = cos(0.1 * dxyResult - t / 7.); // (divisé par 10) devient (* 0.1)

			float colorxy = 128 + 127 * sup / (dxyResult * 0.1 + 1);
			color.x = colorxy;
			color.y = colorxy;
			color.z = colorxy;
			color.w = 255;
		}

	private:

		/*--------------------------------------*\
	|*		Attributs		*|
		 \*-------------------------------------*/

		__device__ void dxy(int i, int j, float* ptrResult) // par exmple
			{
			    float fx = i - dim2;
			    float fy = j - dim2;
			    *ptrResult = sqrt(fx * fx + fy * fy);
			}

	private:

		// Tools
		int dim2;
};

#endif

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/

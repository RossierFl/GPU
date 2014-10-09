#ifndef Fractal_MATH_H_
#define Fractal_MATH_H_

#include <math.h>

class FractalMath {

	public:

		FractalMath(unsigned int n) {
			this->n = n;
		}

		virtual ~FractalMath(void) {
			//rien
		}

		void colorIJ(uchar4* ptrColor, int i, int j) {
			float x = 0;
			float y = 0;
			toXY(i, j, x, y);

			float a = 0;
			float b = 0;
			int k = 0;

			while (k < n && a * a + b * b <= 4) {
				float aCopy = a;
				a = (a * a - b * b) + x;
				b = 2 * aCopy * b + y;
			}
		}

	private:

		// Inputs
		unsigned int n;

};

#endif


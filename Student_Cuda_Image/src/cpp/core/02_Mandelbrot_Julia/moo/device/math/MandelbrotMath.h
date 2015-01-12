#ifndef MANDELBROTMATH_H_
#define MANDELBROTMATH_H_

#include "Fractale.h"

class MandelbrotMath: public Fractale {

	public:

		__device__ MandelbrotMath(int n) :
				Fractale(n) {
		}

		__device__
	       virtual ~MandelbrotMath() {
		}

		__device__
		int indiceArret(double x, double y) {
			double a = 0.0;
			double b = 0.0;
			int k = 0;

			while (((a * a) + (b * b)) <= 4.0 && k <= n) {
				double tempA = a;
				a = (a * a) - (b * b) + x;
				b = 2.0 * tempA * b + y;

				k++;
			}

			return k;
		}
};

#endif

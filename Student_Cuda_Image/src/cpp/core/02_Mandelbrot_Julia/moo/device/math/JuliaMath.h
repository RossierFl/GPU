#ifndef JULIAMATH_H_
#define JULIAMATH_H_

#include "Fractale.h"

class JuliaMath: public Fractale {

	public:

		__device__ JuliaMath(int n, float c1, float c2) :
				Fractale(n) {
			this->c1 = c1;
			this->c2 = c2;
		}

		__device__   virtual ~JuliaMath(void) {
		}

		__device__
		int indiceArret(double x, double y) {
			double a = x;
			double b = y;
			int k = 0;

			while (((a * a) + (b * b)) < 4.0 && k < n) {
				double tempA = a;
				a = (a * a) - (b * b) + c1;
				b = 2.0 * tempA * b + c2;

				k++;
			}
			return k;
		}

	private:

		float c1;
		float c2;
};

#endif

#ifndef FRACTALE_H_
#define FRACTALE_H_

#include <math.h>

#include "CalibreurF.h"
#include "ColorTools.h"

class Fractale {

	public:

		__device__ Fractale(int n) {
			this->n = n;
		}

		__device__  virtual ~Fractale(void) {
		}

		__device__
		virtual int indiceArret(double x, double y) = 0;

		__device__
		void colorXY(uchar4* ptrColor, float x, float y, float t) {
			float k = indiceArret(x, y);
			if (k > n) {
				// Noir
				ptrColor->x = 0;
				ptrColor->y = 0;
				ptrColor->z = 0;
			} else {
				k = 1.0 / n * k;
				ColorTools::HSB_TO_RVB(k, ptrColor); // update color
			}

			ptrColor->w = 255; // opaque
		}

	protected:

		// Input
		int n;
};

#endif

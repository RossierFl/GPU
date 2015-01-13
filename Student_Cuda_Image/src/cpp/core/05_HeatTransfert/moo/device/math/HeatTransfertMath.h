#ifndef HEATTRANSFERTMATH_H_
#define HEATTRANSFERTMATH_H_

#include <math.h>
#include "CalibreurF.h"
#include "ColorTools.h"
#include "IndiceTools.h"

class HeatTransfertMath {

	public:

		__device__ HeatTransfertMath() {
		}

		__device__ virtual ~HeatTransfertMath() {
		}

		__device__
		void getNewPixelValue(float* pixelValue, float* ptrDevImage, float k, int s, int w) {
			float center = ptrDevImage[s];
			float top = ptrDevImage[s - w];
			float down = ptrDevImage[s + w];
			float left = ptrDevImage[s - 1];
			float right = ptrDevImage[s + 1];

			*pixelValue = center + k * (top + down + right + left - 4 * center);
		}
};

#endif

#include "MandelbrotJuliaProvider.h"
#include "MathTools.h"

#define JULIA true /* true|false */
#define MULTI_GPU false /* true|false */

MandelbrotJulia* MandelbrotJuliaProvider::create() {
	int dw = 16 * 60; // =32*30=960
	int dh = 16 * 60; // =32*30=960
	float dt = (100.0 - 30.0) / 400.0; // control animation

#if JULIA
		float c1 = -0.12;
		float c2 = 0.85;
		float x1 = -1.3;
		float x2 = 1.3;
		float y1 = -1.4;
		float y2 = 1.4;
		int n = 52;
#else
		float c1 = -0.12;
		float c2 = 0.85;
		float x1 = -1.3968;
		float x2 = -1.3578;
		float y1 = -0.03362;
		float y2 = 0.0013973;
		int n = 102;
#endif

	return new MandelbrotJulia(JULIA, MULTI_GPU, dw, dh, dt, n, c1, c2, x1, x2, y1, y2);
}

ImageFonctionel* MandelbrotJuliaProvider::createGL() {
	ColorRGB_01* ptrColorTitre = new ColorRGB_01(0, 0, 0);
	return new ImageFonctionel(create(), ptrColorTitre);
}

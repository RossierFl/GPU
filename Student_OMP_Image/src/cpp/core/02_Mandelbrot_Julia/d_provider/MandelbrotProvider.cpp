#include "MandelbrotProvider.h"

FractalImage* FractalProvider::create() {
	const unsigned int N = 100;

	int dw = 16 * 60; // =32*30=960
	int dh = 16 * 60; // =32*30=960

	return new FractalImage(dw, dh, N);
}

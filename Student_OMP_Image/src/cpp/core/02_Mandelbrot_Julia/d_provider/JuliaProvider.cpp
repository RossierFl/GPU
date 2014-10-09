#include "RipplingProvider.h"

RipplingImage* RipplingProvider::create() {
	float dt = 1;

	int dw = 16 * 60; // =32*30=960
	int dh = 16 * 60; // =32*30=960

	return new RipplingImage(dw, dh, dt);
}


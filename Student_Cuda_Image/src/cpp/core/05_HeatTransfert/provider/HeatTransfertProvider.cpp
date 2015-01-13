#include "HeatTransfertProvider.h"
#include "MathTools.h"

HeatTransfert* HeatTransfertProvider::create() {
	int dw = 960; // =32*30=960
	int dh = 960; // =32*30=960
	float k = 0.25;

	return new HeatTransfert(dw, dh, k);
}

Image* HeatTransfertProvider::createGL(void) {
	ColorRGB_01* ptrColorTitre = new ColorRGB_01(0, 0, 0);
	return new Image(create(), ptrColorTitre);
}

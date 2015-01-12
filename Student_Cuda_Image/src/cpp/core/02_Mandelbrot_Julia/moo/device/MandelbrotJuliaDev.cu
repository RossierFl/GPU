#include "IndiceTools.h"
#include "Indice2D.h"
#include "cudaTools.h"
#include "Device.h"
#include "DomaineMath.h"
#include "Fractale.h"
#include "MandelbrotMath.h"
#include "JuliaMath.h"

__global__ void fractale(bool isJulia, uchar4* ptrDevPixels, int w, int h, DomaineMath domaineMath, int n, float t, float c1, float c2) {
	const int TID = Indice2D::tid();
	const int NB_THREAD = Indice2D::nbThread();
	const int WH = w * h;

	Fractale* math = 0;
	if (isJulia) {
		math = new JuliaMath(n, c1, c2);
	} else {
		math = new MandelbrotMath(n);
	}

	int s = TID;
	while (s < WH) {
		int pixelI;
		int pixelJ;
		IndiceTools::toIJ(s, w, &pixelI, &pixelJ); // update (pixelI, pixelJ)

		// (i,j) domaine ecran
		// (x,y) domaine math
		double x;
		double y;
		domaineMath.toXY(pixelI, pixelJ, &x, &y);

		uchar4 color;
		math->colorXY(&color, x, y, t); // update color
		ptrDevPixels[s] = color;

		s += NB_THREAD;
	}

	delete math;
}


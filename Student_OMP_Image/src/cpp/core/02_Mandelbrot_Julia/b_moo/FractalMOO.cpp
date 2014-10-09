#include <iostream>
#include <omp.h>

#include "FractalMOO.h"
#include "OmpTools.h"
#include "FractalMath.h"
#include "IndiceTools.h"

using std::cout;
using std::endl;
using std::string;

FractalMOO::FractalMOO(unsigned int w, unsigned int h, unsigned int n) {
	this->w = w;
	this->h = h;
	this->n = n;
	this->isEntrelacement = false;
}

FractalMOO::~FractalMOO(void) {
	// rien
}

void FractalMOO::process(uchar4* ptrTabPixels, int w, int h) {
	if (isEntrelacement) {
		entrelacementOMP(ptrTabPixels); // Plus lent
	} else {
		forAutoOMP(ptrTabPixels);  // Plus rapide
	}

	isEntrelacement = !isEntrelacement;  // Pour tester que les deux implementations fonctionnent
}

void FractalMOO::animationStep() {
}

{
	for (int ix = 0; ix < w; ++ix){
		for (int iy = 0; iy < h; ++iy)
		{
			std::complex<double> c(cxmin + ix/(w-1.0)*(cxmax-cxmin), cymin + iy/(h-1.0)*(cymax-cymin));
			std::complex<double> z = 0;
			unsigned int iterations;

			for (iterations = 0; iterations < max_iterations && std::abs(z) < 2.0; ++iterations)
			z = z*z + c;

			image[ix][iy] = (iterations == max_iterations) ? set_color : non_set_color;

		}
	}
}

/**
 * Code entrainement Cuda
 */
void FractalMOO::entrelacementOMP(uchar4* ptrTabPixels) {
	FractalMath FractalMath(w, h); // ici pour preparer cuda
	const int WH = w * h;

#pragma omp parallel
	{
		const int NB_THREAD = OmpTools::getNbThread(); // dans region parallel
		const int TID = OmpTools::getTid();
		int s = TID; // in [0,...

		int i;
		int j;
		while (s < WH) {
			IndiceTools::toIJ(s, w, &i, &j); // s[0,W*H[ --> i[0,H[ j[0,W[

			FractalMath.colorIJ(&ptrTabPixels[s], i, j, t);

			s += NB_THREAD;
		}
	}
}

/**
 * Code naturel et direct OMP
 */
void FractalMOO::forAutoOMP(uchar4* ptrTabPixels) {
	FractalMath FractalMath(w, h); // ici pour preparer cuda

#pragma omp parallel for
	for (int i = 0; i < h; i++) {
		for (int j = 0; j < w; j++) {
			// int s = i * W + j;
			int s = IndiceTools::toS(w, i, j);    // i[0,H[ j[0,W[  --> s[0,W*H[

			FractalMath.colorIJ(&ptrTabPixels[s], i, j, t);
		}
	}
}


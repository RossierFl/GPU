#include "Indice2D.h"
#include "IndiceTools.h"
#include "DomaineMath.h"
#include "cudaTools.h"
#include "Device.h"
#include "HeatTransfertMath.h"
#include "CalibreurCudas.h"
#include "ColorTools_GPU.h"
#include <stdio.h>

__global__ void heatTransfertDiffusion(float* ptrDevImageA, float* ptrDevImageB, bool isImageAInput, int w, int h, float k);
__global__ void heatTransfertEcrasement(float* ptrDevInputHeater, float* ptrDevInputImage, float* ptrDevOutput, int w, int h);
__global__ void heatTransfertConvertData(CalibreurCudas calibreurCuda, float* ptrDevInput, uchar4* ptrDevImage, int w, int h);

__global__ void heatTransfertDiffusion(float* ptrDevImageA, float* ptrDevImageB, bool isImageAInput, int w, int h, float k) {
	const int TID = Indice2D::tid();
	const int NB_THREAD = Indice2D::nbThread();
	const int WH = w * h;

	HeatTransfertMath* heatTransfertMath = new HeatTransfertMath();

	int s = TID;
	while (s < WH) {
		int pixelI = 0;
		int pixelJ = 0;
		IndiceTools::toIJ(s, w, &pixelI, &pixelJ);

		if (pixelI != 0 && pixelI != h && pixelJ != 0 && pixelJ != w) { //not on the side of the image
			if (isImageAInput) {
				heatTransfertMath->getNewPixelValue(&ptrDevImageA[s], ptrDevImageB, k, s, w); // update color
			} else {
				heatTransfertMath->getNewPixelValue(&ptrDevImageB[s], ptrDevImageA, k, s, w); // update color
			}
		}

		s += NB_THREAD;
	}

	delete heatTransfertMath;
}
__global__ void heatTransfertEcrasement(float* ptrDevInputHeat, float* ptrDevInputImg, float* ptrDevOut, int w, int h) {
	const int TID = Indice2D::tid();
	const int NB_THREAD = Indice2D::nbThread();
	const int WH = w * h;

	uint s = TID;
	while (s < WH) {
		ptrDevOut[s] = ptrDevInputImg[s];

		if (ptrDevInputHeat[s] != 0.0) {	  //ok an if, but most of the image will be copied
			ptrDevOut[s] = ptrDevInputHeat[s];
		}

		s += NB_THREAD;
	}
}
__global__ void heatTransfertConvertData(CalibreurCudas calibreurCuda, float* ptrDevInput, uchar4* ptrDevImg, int w, int h) {
	const int TID = Indice2D::tid();
	const int NB_THREAD = Indice2D::nbThread();
	const int WH = w * h;

	int s = TID;
	while (s < WH) {
		float hue = calibreurCuda.calibrate(ptrDevInput[s]);
		ColorTools::HSB_TO_RVB(hue, &ptrDevImg[s]);

		s += NB_THREAD;
	}
}

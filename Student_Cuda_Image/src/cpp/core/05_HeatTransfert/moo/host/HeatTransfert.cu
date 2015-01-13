#include <assert.h>
#include <stdio.h>
#include "HeatTransfert.h"
#include "Device.h"
#include "MathTools.h"

#define NB_ITERATION_AVEUGLE 2

extern __global__ void heatTransfertDiffusion(float* ptrDevImageA,float* ptrDevImageB, bool isImageAInput, int w, int h,float k);
extern __global__ void heatTransfertEcrasement(float* ptrDevInputHeater, float* ptrDevInputImage,float* ptrDevOutput, int w, int h);
extern __global__ void heatTransfertConvertData(CalibreurCudas calibreurCuda,float* ptrDevInput, uchar4* ptrDevImage, int w, int h);

HeatTransfert::HeatTransfert(int w, int h, float k) :
		calibreurCuda(0.0, 1.0, 0.7, 0.0) {
	// Inputs
	this->w = w;
	this->h = h;
	this->k = k;
	// Tools
	this->dg = dim3(8, 8, 1); // disons a optimiser
	this->db = dim3(16, 16, 1); // disons a optimiser

	//Outputs
	this->title = "[API Image] : HeatTransfert CUDA";

	// Check:
	Device::assertDim(dg, db);
	assert(w == h);
	size_t sizeImages = w * h * sizeof(float);
	//init
	//imageInit all to zero
	HANDLE_ERROR(cudaMalloc((void** ) &ptrDevImageInit, sizeImages)); // Device memory allocation (*)
	HANDLE_ERROR(cudaMemset(ptrDevImageInit, 0, sizeImages));

	HANDLE_ERROR(cudaMalloc((void** ) &ptrDevImageA, sizeImages)); // Device memory allocation (*)
	HANDLE_ERROR(cudaMemset(ptrDevImageA, 0, sizeImages));

	HANDLE_ERROR(cudaMalloc((void** ) &ptrDevImageB, sizeImages)); // Device memory allocation (*)
	HANDLE_ERROR(cudaMemset(ptrDevImageB, 0, sizeImages));

	//imageHeater all zero with some heater or "cooler"
	HANDLE_ERROR(cudaMalloc((void** ) &ptrDevImageHeater, sizeImages)); // Device memory allocation (*)
	HANDLE_ERROR(cudaMemset(ptrDevImageHeater, 0, sizeImages));

	float *imageHeaterCPU = new float[w * h];

	// ary[i][j] is then rewritten as imageHeaterCPU[i*h+j]
	for (int i = 0; i <= h; i++)    //take it to zero to avoid something strange
	        {
		for (int j = 0; j <= w; j++) {
			imageHeaterCPU[i * h + j] = 0.0;
		}
	}
	//single cooler point
	imageHeaterCPU[295 * h + 400] = 0.2;
	imageHeaterCPU[400 * h + 295] = 0.2;
	imageHeaterCPU[505 * h + 400] = 0.2;
	imageHeaterCPU[400 * h + 505] = 0.2;

	//up cooler
	for (int i = 179; i <= 195; i++) {
		for (int j = 179; j <= 195; j++) {
			imageHeaterCPU[i * h + j] = 0.2;
		}
		for (int j = 605; j <= 621; j++) {
			imageHeaterCPU[i * h + j] = 0.2;
		}
	}

	//down cooler
	for (int i = 605; i <= 621; i++) {
		for (int j = 179; j <= 195; j++) {
			imageHeaterCPU[i * h + j] = 0.2;
		}
		for (int j = 605; j <= 621; j++) {
			imageHeaterCPU[i * h + j] = 0.2;
		}
	}

	//main heater
	for (int i = 300; i <= 500; i++) {
		for (int j = 300; j <= 500; j++) {
			imageHeaterCPU[i * h + j] = 1.0;
		}
	}

	//copy this tab to GPU
	HANDLE_ERROR(cudaMemcpy(ptrDevImageHeater, imageHeaterCPU, sizeImages, cudaMemcpyHostToDevice));    // Host -> Device
	delete[] imageHeaterCPU;

	//ecrase A with imageHeater;

	heatTransfertEcrasement<<<dg,db>>>(ptrDevImageHeater,ptrDevImageA,ptrDevImageA, w, h);
	Device::synchronize();
	Device::checkKernelError("heatTransfertEcrasement");
}

HeatTransfert::~HeatTransfert() {
	HANDLE_ERROR(cudaFree(ptrDevImageHeater));
	HANDLE_ERROR(cudaFree(ptrDevImageInit));
	HANDLE_ERROR(cudaFree(ptrDevImageA));
	HANDLE_ERROR(cudaFree(ptrDevImageB));
}

/**
 * Override
 */
void HeatTransfert::animationStep() {
}

/**
 * Override
 */
void HeatTransfert::runGPU(uchar4* ptrDevPixels) {
	//iteration
	float* iterationOutput;
	for (int i = 0; i <= NB_ITERATION_AVEUGLE; i++) {
		heatTransfertDiffusion<<<dg,db>>>(ptrDevImageA,ptrDevImageB, (i+1)%2, w, h, k);
		Device::synchronize();

		if ((i + 1) % 2 == 1)
			iterationOutput = ptrDevImageB;
		else
			iterationOutput = ptrDevImageA;

		heatTransfertEcrasement<<<dg,db>>>(ptrDevImageHeater,iterationOutput,iterationOutput, w, h);
		Device::synchronize();
	}

	//show on screen what is going on
	heatTransfertConvertData<<<dg,db>>>(this->calibreurCuda, iterationOutput,ptrDevPixels, w, h);
	//Device::synchronize();
}

/**
 * Override
 */
float HeatTransfert::getT() {
	return 0.0;
}

/**
 * Override
 */
int HeatTransfert::getW() {
	return w;
}

/**
 * Override
 */
int HeatTransfert::getH() {
	return h;
}

/**
 * Override
 */
string HeatTransfert::getTitle() {
	return title;
}

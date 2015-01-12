#include <assert.h>

#include "MandelbrotJulia.h"
#include "Device.h"
#include "MathTools.h"
#include <stdio.h>

__global__ void fractale(bool isJulia, uchar4* ptrDevPixels, int w, int h, DomaineMath domaineMath, int n, float t, float c1, float c2);

MandelbrotJulia::MandelbrotJulia(bool isJulia, bool isMultiGPU, int w, int h, float dt, int n, float c1, float c2, float x1, float x2, float y1, float y2) :
		variateurAnimation(IntervalF(30, 100), dt) {
	// Inputs
	this->w = w;
	this->h = h;
	this->n = n;

	this->c1 = c1;
	this->c2 = c2;

	this->isJulia = isJulia;
	this->isMultiGPU = isMultiGPU;

	// Tools
	this->dg = dim3(8, 8, 1); // disons a optimiser
	this->db = dim3(16, 16, 1); // disons a optimiser
	this->t = 0;
	ptrDomaineMathInit = new DomaineMath(x1, y1, x2, y2);

	//Outputs
	this->title = "[API Image Fonctionelle] : Mandelbrot or Julia zoomable";
	if(isMultiGPU) {
		this->title += " [Multi GPU]";
	}

	Device::assertDim(dg, db);
	assert(w == h);
}

MandelbrotJulia::~MandelbrotJulia() {
	delete ptrDomaineMathInit;
}

/**
 * Override
 */
void MandelbrotJulia::animationStep() {
	this->t = variateurAnimation.varierAndGet();
}

/**
 * Override
 */
void MandelbrotJulia::runGPU(uchar4* ptrDevPixels, const DomaineMath& domaineMath) {
	if (!isMultiGPU) {
		// Call kernel
		fractale<<<dg,db>>>(isJulia, ptrDevPixels, w, h, domaineMath, getT(), t, c1, c2);
		Device::checkKernelError("kernel error: fractale");
		Device::synchronize();
	} else {
		const uint NB_GPU = Device::getDeviceCount();

		/* Enable P2P */
		Device::p2pEnableALL();

		/* Compute steps for each GPU */
		uint remainingH = h;
		const uint stepH = h / NB_GPU;
		uint steps[NB_GPU];
		for (int device = 0; device < NB_GPU; device++) {
			if (device == NB_GPU - 1) {
				steps[device] = remainingH;
			} else {
				steps[device] = stepH;
			}
			remainingH -= steps[device];
		}

		/* Processing */
#pragma omp parallel for
		for (int device = 0; device < NB_GPU; device++) {
			bool isFirst = device == 0;

			// set current device
			cudaSetDevice(device);

			// start of data to process on this GPU
			uint offset = w * device * steps[device];
			uchar4* start = ptrDevPixels + offset;
			uchar4* targetCurrentDevResult = ptrDevPixels;

			if(!isFirst) {
				targetCurrentDevResult = NULL;
				HANDLE_ERROR(cudaMalloc(&targetCurrentDevResult, sizeof(uchar4) * steps[device]));
			}

			// call kernel to compute a step
			fractale<<<dg,db>>>(isJulia, targetCurrentDevResult, w, steps[device], domaineMath, getT(), t, c1, c2);
			Device::checkKernelError("kernel error: fractale");
			Device::synchronize();

			// Le premier GPU contient toute l'image, mais traite que les premières lignes
			// Les autres sont traitées par les autres GPUs, il faut donc copier leur résultat sur le
			// première GPU afin qu'OpenGL puisse tout afficher
			if(!isFirst) {
				HANDLE_ERROR(cudaMemcpy(start, targetCurrentDevResult, sizeof(uchar4) * steps[device], cudaMemcpyDeviceToDevice));
				HANDLE_ERROR(cudaFree(targetCurrentDevResult));
			}
		}
	}
}

/**
 * Override
 */
DomaineMath* MandelbrotJulia::getDomaineMathInit() {
	return ptrDomaineMathInit;
}

/**
 * Override
 */
float MandelbrotJulia::getT() {
	return t;
}

/**
 * Override
 */
int MandelbrotJulia::getW() {
	return w;
}

/**
 * Override
 */
int MandelbrotJulia::getH() {
	return h;
}

/**
 * Override
 */
string MandelbrotJulia::getTitle() {
	return title;
}

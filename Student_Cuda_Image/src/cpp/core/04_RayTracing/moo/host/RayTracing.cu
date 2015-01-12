#include <assert.h>

#include "RayTracing.h"
#include "Device.h"
#include "MathTools.h"
#include <stdio.h>

__global__ void rayTracingGPU(uchar4* ptrDevPixels, int w, int h, float t, Sphere* spheres, int n);

RayTracing::RayTracing(int w, int h, float dt, double x1, double y1, double x2, double y2, Sphere* spheres, int n) :
		variateurAnimation(IntervalF(0, 10), dt) {
	// Inputs
	this->w = w;
	this->h = h;

	this->spheres = spheres;
	this->n = n;

	// Tools
	this->dg = dim3(8, 8, 1); // TODO disons a optimiser
	this->db = dim3(16, 16, 1); // TODO disons a optimiser
	this->t = variateurAnimation.varierAndGet();

	//Outputs
	this->title = "RayTracing non-zoomable CUDA";

	// control
	Device::assertDim(dg, db);
	assert(w == h);
}

RayTracing::~RayTracing() {
}

void RayTracing::runGPU(uchar4* ptrDevPixels) {
	Sphere* spheresDevGRAM = NULL;
	HANDLE_ERROR(cudaMalloc(&spheresDevGRAM, n * sizeof(Sphere)));
	HANDLE_ERROR(cudaMemcpy(spheresDevGRAM, spheres, n * sizeof(Sphere), cudaMemcpyHostToDevice));
	rayTracingGPU<<<dg,db>>>(ptrDevPixels, w, h, t, spheresDevGRAM, n);
	cudaFree(spheresDevGRAM);
	cudaDeviceSynchronize();
}

/**
 * Override
 */
void RayTracing::animationStep() {
	this->t = variateurAnimation.varierAndGet();
}

/**
 * Override
 */
float RayTracing::getT() {
	return t;
}

/**
 * Override
 */
int RayTracing::getW() {
	return w;
}

/**
 * Override
 */
int RayTracing::getH() {
	return h;
}

/**
 * Override
 */
string RayTracing::getTitle() {
	return title;
}

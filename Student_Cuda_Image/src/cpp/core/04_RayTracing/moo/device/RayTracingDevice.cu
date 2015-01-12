#include "Indice2D.h"
#include "IndiceTools.h"
#include "DomaineMath.h"
#include "cudaTools.h"
#include "Device.h"
#include "RayTracingMath.h"
#include "Sphere.h"

__global__ void rayTracingGPU(uchar4* ptrDevPixels, int w, int h, float t, Sphere* spheres, int n) {
	const int TID = Indice2D::tid();
	const int NB_THREAD = Indice2D::nbThread();
	const int WH = w * h;

	RayTracingMath* rayTracingMath = new RayTracingMath();

	int s = TID;
	while (s < WH) {
		uchar4 color;
		int x;
		int y;
		IndiceTools::toIJ(s, w, &x, &y);
		rayTracingMath->colorXY(&color, x, y, t, spheres, n);
		ptrDevPixels[s] = color;
		s += NB_THREAD;
	}

	delete rayTracingMath;
}


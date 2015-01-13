#ifndef RAYTRACINGMATH_H_
#define RAYTRACINGMATH_H_

#include "ColorTools.h"
#include <float.h>

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

class RayTracingMath {
    public:
	__device__ RayTracingMath()
	    {
	    }
	__device__ virtual ~RayTracingMath()
	    {
	    }
	__device__ float linearInterp(float v0, float v1, float t)
	    {
	    return (1 - t) * v0 + t * v1;
	    }
	__device__ void colorXY(uchar4* ptrColor, int x, int y, float t, Sphere* spheres, int n)
	    {
	    float minDist = FLT_MAX; // from float.h

	    float2 solXY;
	    solXY.x = x;
	    solXY.y = y;

	    // black
	    ptrColor->x = 0;
	    ptrColor->y = 0;
	    ptrColor->z = 0;
	    ptrColor->w = 1;
	    for (int i = 0; i < n; i++) {
		float h2 = spheres[i].hCarre(solXY);
		bool under = spheres[i].isUnder(h2);
		if (under) {
		    float dz = spheres[i].dz(h2);
		    float dist = spheres[i].distance(dz);
		    if (dist != NAN && dist < minDist) {
			minDist = dist;
			ColorTools::HSB_TO_RVB(fmodf(spheres[i].getHueStart() + t, 1.0f), 1, spheres[i].brightness(dz), ptrColor);
		    }
		}
	    }
	    }

	__device__ float3 float3LinearInterp(float3 c0, float3 c1, float f)
	    {
	    float3 res;
	    res.x = linearInterp(c0.x, c1.x, f);
	    res.y = linearInterp(c0.y, c1.y, f);
	    res.z = linearInterp(c0.z, c1.z, f);
	    return res;
	    }
};


#endif 

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/

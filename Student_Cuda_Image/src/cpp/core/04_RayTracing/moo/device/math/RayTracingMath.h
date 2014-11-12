#ifndef RAYTRACINGMATH_H_
#define RAYTRACINGMATH_H_

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "CalibreurF.h"
#include "ColorTools.h"
#include "Sphere.h"
#include "Indice2D.h"
#include <float.h>


/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/


class RayTracingMath
{

	/*--------------------------------------*\
	|*		Constructor		*|
	 \*-------------------------------------*/

public:

	__device__ RayTracingMath()
	{
	}

	__device__ virtual ~RayTracingMath()
	{
	}

	/*--------------------------------------*\
	|*		Methodes		*|
	 \*-------------------------------------*/

public:

	__device__ inline float lerp(float v0, float v1, float t)
	{
		return (1 - t) * v0 + t * v1;
	}

	__device__ inline float3 float3Lerp(float3 c0, float3 c1, float f)
	{
		float3 res;
		res.x = lerp(c0.x, c1.x, f);
		res.y = lerp(c0.y, c1.y, f);
		res.z = lerp(c0.z, c1.z, f);
		return res;
	}

	__device__ void colorXY(uchar4* ptrColor, int x, int y, float t, Sphere* spheres, int n)
	{
		float2 solXY;
		solXY.x = x;
		solXY.y = y;

		float minDist = FLT_MAX;
		float3 minDistColor { 0.0f, 0.0f, 0.0f };

		/* Reset color to black */
		ptrColor->x = 0;
		ptrColor->y = 0;
		ptrColor->z = 0;
		ptrColor->w = 1;

		/* Compute color of spheres */
		int i = 0;
		while (i < n)
		{
			float h2 = spheres[i].hCarre(solXY);
			bool isUnder = spheres[i].isEnDessous(h2);
			if (isUnder)
			{
				float dz = spheres[i].dz(h2);
				float dist = spheres[i].distance(dz);

				/*if (dist != NAN && dist < minDist)
				{
					ColorTools::HSB_TO_RVB(fmodf(spheres[i].getHueStart() + t, 1.0f), 1, spheres[i].brightness(dz), ptrColor);
					minDist = dist;
				}*/
				bool b = isUnder && (dist!=NAN && dist<minDist);
				float3 newColor;
				newColor.x = fmodf(spheres[i].getHueStart() + t, 1.0f);
				newColor.y = 1;
				newColor.z = spheres[i].brightness(dz);
				minDistColor = float3Lerp(minDistColor, newColor, b);
				minDist = lerp(minDist, dist, b);
			}
			i++;
		}
		ColorTools::HSB_TO_RVB(minDistColor, ptrColor);
	}

	/*--------------------------------------*\
	|*		Attributs		*|
	 \*-------------------------------------*/
};


#endif



/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/

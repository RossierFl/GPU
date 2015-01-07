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

	__device__ virtual ~RayTracingMath(void)
	    {
	    }

	/*--------------------------------------*\
	|*		Methodes		*|
	 \*-------------------------------------*/

    public:

	__device__ //linear interpolation, good to replace simple if inside GPU/shader :D
		float lerp(float v0, float v1, float t) {
		  return (1-t)*v0 + t*v1;
		}

	__device__ //linear interpolation, good to replace simple if inside GPU/shader :D
		float3 float3Lerp(float3 c0, float3 c1, float f) {
		float3 res;
		  res.x = lerp(c0.x,c1.x,f);
		  res.y = lerp(c0.y,c1.y,f);
		  res.z = lerp(c0.z,c1.z,f);
		  return res;
		}

	__device__
	void colorXY(uchar4* ptrColor,int x, int y,float t, Sphere* spheres, int n)
	    {

	    //this function is faster using the if than the lerps because so little is done in the ifs !
		int i = 0;
		float2 solXY;
		solXY.x =x;
		solXY.y =y;
		float minDist = FLT_MAX;
		//float3 minDistColor{0.0f,0.0f,0.0f};
		ptrColor->x=0;
		ptrColor->y=0;
		ptrColor->z=0;
		ptrColor->w=1;
		while(i<n)
		    {
			float h2 = spheres[i].hCarre(solXY);
			bool isUnder = spheres[i].isEnDessous(h2);
			if(isUnder){
			float dz = spheres[i].dz(h2);
			float dist = spheres[i].distance(dz);

			    if(dist!=NAN && dist<minDist){
				ColorTools::HSB_TO_RVB(fmodf(spheres[i].getHueStart()+t,1.0f), 1, spheres[i].brightness(dz), ptrColor);
				minDist=dist;
			    }
			    /*float3 newColor;
			    newColor.x = fmodf(spheres[i].getHueStart()+t,1.0f);
			    newColor.y = 1;
			    newColor.z = spheres[i].brightness(dz);
			    minDistColor = float3Lerp(minDistColor, newColor,isUnder && (dist!=NAN && dist<minDist));
			    minDist = lerp(minDist, dist, isUnder && (dist!=NAN && dist<minDist));*/
			}
			i++;
		    }
		//ColorTools::HSB_TO_RVB(minDistColor, ptrColor);
	    }

	/*--------------------------------------*\
	|*		Attributs		*|
	 \*-------------------------------------*/
    };



#endif 



/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/

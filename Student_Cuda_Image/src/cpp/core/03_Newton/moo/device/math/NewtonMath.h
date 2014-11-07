#ifndef NEWTONMATH_H_
#define NEWTONMATH_H_

#include <math.h>

#include "CalibreurF.h"
#include "ColorTools.h"


/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/


class NewtonMath
    {

	/*--------------------------------------*\
	|*		Constructor		*|
	 \*-------------------------------------*/

    public:

	__device__ NewtonMath()
	    {
		//all answers
		xa.x = 1.0;
		xa.y = 0.0;

		xb.x = -0.5;
		xb.y = sqrt(1.5);

		xc.x = -0.5;
		xc.y = -sqrt(1.5);
	    }

	__device__ virtual ~NewtonMath(void)
	    {
	    }

    public :
	struct vec2 //simple vec2 -> similar to glsl shader
	    {
	__device__
		vec2(float xin, float yin):x(xin),y(yin){};
	__device__
		vec2(){};
		float x;
		float y;
	    };

	/*--------------------------------------*\
	|*		Methodes		*|
	 \*-------------------------------------*/

    public:

	__device__
	int indiceArret(float x1, float x2, unsigned int n, float eX, float eF,
		float eX_Star,float* jacobianMat)
	    {

	//float crtX1 = x1;
	//float crtX2 = x2;
	vec2 currentX;
	currentX.x = x1;
	currentX.y = x2;

	vec2 nextX;
	vec2 resX;
	int i = 0;
	while(i < n)
	    {
	    computeJacobianMat(currentX,jacobianMat);
	    inverseMat(jacobianMat);
	    multMatrixVector2f(jacobianMat,vec2(f1(currentX),f2(currentX)),&resX);

	    nextX.x = currentX.x - resX.x;
	    nextX.y = currentX.y - resX.y;

	    if(squaredMag(vec2(currentX.x-xa.x,currentX.y-xa.y))/
		    squaredMag(xa) < eX_Star)
		{
		return BLACK;
		}
	    else if(squaredMag(vec2(currentX.x-xb.x,currentX.y-xb.y))/
		    squaredMag(xb) < eX_Star)
		{
		return GREY;
		}
	    else if(squaredMag(vec2(currentX.x-xc.x,currentX.y-xc.y))/
		    squaredMag(xc) < eX_Star)//to check
		{
		return WHITE;
		}

	    if(squaredMag(vec2(currentX.x-nextX.x,currentX.y-nextX.y))/squaredMag(nextX) < eX ||
		    squaredMag(vec2(f1(currentX)-f1(nextX),f2(currentX)-f2(nextX)))/squaredMag(vec2(f1(nextX),f2(nextX))) < eF)
		{

		float xaNextX = squaredMag(vec2(nextX.x-xa.x,nextX.y-xa.y))/squaredMag(xa);
		float xbNextX = squaredMag(vec2(nextX.x-xb.x,nextX.y-xb.y))/squaredMag(xb);
		float xcNextX = squaredMag(vec2(nextX.x-xc.x,nextX.y-xc.y))/squaredMag(xc);

		/*if(xaNextX < xbNextX)
		    if(xaNextX < xcNextX)return BLACK;
		    else return WHITE;
		else
		    if(xbNextX < xcNextX) return GREY;
		    else return WHITE;*/

		//replace the if above, more efficient (at least on shader)
		return lerp(
			lerp(WHITE,GREY,xbNextX < xcNextX)
			,lerp(WHITE,BLACK,xaNextX < xcNextX)
			,xaNextX < xbNextX);
		}
	    currentX = nextX;
	    i++;
	    }
	    return ORANGE;//didnt converge
	    }

	__device__ //linear interpolation, good to replace simple if inside GPU/shader :D
	float lerp(float v0, float v1, float t) {
	  return (1-t)*v0 + t*v1;
	}

	__device__
	float squaredMag(vec2 x)//quared magnitude
	    {
	    return x.x*x.x+x.y*x.y;
	    }

	__device__
	float f1(vec2 x)//given in TP
	    {
	    return (x.x*x.x*x.x)-(3*x.x*(x.y*x.y))-1;
	    }

	__device__
	float f2(vec2 x)//given in TP
	    {
	    return (x.y*x.y*x.y)-(3*x.y*(x.x*x.x));
	    }

	__device__
	void computeJacobianMat(vec2 x, float* matrixDevicePtr)//pointer from device
	    {
	    matrixDevicePtr[0] = (3*x.x*x.x)-(3*x.y*x.y);
	    matrixDevicePtr[1] = -6*x.x*x.y;
	    matrixDevicePtr[2] = -6*x.y*x.x;
	    matrixDevicePtr[3] = 3*x.y*x.y-3*x.x*x.x;
	    }

	__device__
	float detMat(float* matrixDevicePtr)//pointer from device
	    {
	    return (matrixDevicePtr[0]*matrixDevicePtr[3])-(matrixDevicePtr[1]*matrixDevicePtr[2]);
	    }

	__device__
	void inverseMat(float* matrixDevicePtr)//pointer from device
	    {
	    float det = detMat(matrixDevicePtr);
	    float tempMat[4];//copy temp
	    tempMat[0] = matrixDevicePtr[0];
	    tempMat[1] = matrixDevicePtr[1];
	    tempMat[2] = matrixDevicePtr[2];
	    tempMat[3] = matrixDevicePtr[3];
	    matrixDevicePtr[0] = tempMat[3]/det;
	    matrixDevicePtr[1] = -tempMat[1]/det;
	    matrixDevicePtr[2] = -tempMat[2]/det;
	    matrixDevicePtr[3] = tempMat[0]/det;
	    }

	__device__
	void multMatrixVector2f(float* matrixDevicePtr, vec2 x, vec2* res)
	    {
	    res->x = matrixDevicePtr[0]*x.x+matrixDevicePtr[1]*x.y;
	    res->y = matrixDevicePtr[2]*x.x+matrixDevicePtr[3]*x.y;
	    }

	__device__
	void colorXY(uchar4* ptrColor,float x, float y,unsigned int n,float eX,float eF,
		float eX_Star,float* jacobianMat)
	    {
	    int resColor = indiceArret(x,y,n,eX,eF,eX_Star,jacobianMat);
	    switch(resColor)
		{
		case BLACK :
		ptrColor->x = 0; // BLACK
		ptrColor->y = 0; // BLACK
		ptrColor->z = 0; // BLACK
		break;
		case GREY :
		ptrColor->x = 211; // GREY
		ptrColor->y = 211; // GREY
		ptrColor->z = 211; // GREY
		break;
		case WHITE :
		ptrColor->x = 255; // WHITE
		ptrColor->y = 255; // WHITE
		ptrColor->z = 255; // WHITE
		break;
		case ORANGE :
		ptrColor->x = 255; // ORANGE
		ptrColor->y = 160; // ORANGE
		ptrColor->z = 0; // ORANGE
		break;
		}

	    ptrColor->w = 255; // opacity to 1
	    }

	/*--------------------------------------*\
	|*		Attributs		*|
	 \*-------------------------------------*/
    protected:

	//answers
	struct vec2 xa;
	struct vec2 xb;
	struct vec2 xc;

	//may I use an ENUM here ????? -- didn't try
	const static int BLACK = 0;
	const static int GREY = 1;
	const static int WHITE = 2;
	const static int ORANGE = 3;//did not converge
    };



#endif 



/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/

#ifndef CONVOLUTIONMATH_H_
#define CONVOLUTIONMATH_H_

#include "MathTools.h"

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

class ConvolutionMath
    {

	/*--------------------------------------*\
	|*		Constructor		*|
	 \*-------------------------------------*/

    public:

	__device__ ConvolutionMath(int w, int h)
	    {
	this->w = w;
	this->h = h;
	    }

	__device__ ConvolutionMath(const ConvolutionMath& source)
	    {
	    // rien
	    }

	/*--------------------------------------*\
	|*		Methodes		*|
	 \*-------------------------------------*/

    public:

	/**
	 * x=pixelI
	 * y=pixelJ
	 */
	__device__
	void colorIJ(uchar4* ptrColor, uchar4* ptrDevPixels, float* ptrDeviceNoyau, int k, int i, int j, int s, float t)
	    {
	unsigned char levelGris;

	f(ptrColor, ptrDevPixels, ptrDeviceNoyau,k,levelGris, i, j, s, t); // update levelGris

	//	ptrOutputColor->x = levelGris;
	//	ptrOutputColor->y = levelGris;
	//	ptrOutputColor->z = levelGris;
	// trololololo

	ptrColor->w = 255; // opaque
	    }

    private:

	__device__
	void firstLine(uchar4* ptrColor, uchar4* ptrDevPixels, float* ptrDeviceNoyau, unsigned char& levelGris, int i, int h, int s)
	    {
	if(i==0)
	    {
	    levelGris = 0;
	    }
	else if(i>0 && i<h)
	    {
	    levelGris = 0;
	    }
	else if(i == h)
	    {
	    levelGris = 0;
	    }
	    }

	/*
	 * s1 s2 s3
	 * s4 s5 s6
	 * s7 s8 s9
	 */
	__device__
	void middleLines(uchar4* ptrColor, uchar4* ptrDevPixels, float* ptrDeviceNoyau, int k, unsigned char& levelGris, int i, int j, int h, int s)
	    {
	    int ss = (k*k)/2;
	    if(i==0)
		{
		levelGris = 0;
		}
	    else if(i>0 && i<h)
		{
		float sum = 0.0f;
		int k2 = k/2;
		for(int v = 1;v<k2;v++)
		    {
		    for(int u = 1;u<k2;u++)
			{
			// bas droite
			sum+=ptrDeviceNoyau[(ss+v*k)+u]*ptrDevPixels[(s+v*w)+u].x;
			// haut droite
			sum+=ptrDeviceNoyau[(ss-v*k)+u]*ptrDevPixels[(s-v*w)+u].x;
			// bas gauche
			sum+=ptrDeviceNoyau[(ss+v*k)-u]*ptrDevPixels[(s+v*w)-u].x;
			// haut gauche
			sum+=ptrDeviceNoyau[(ss-v*k)-u]*ptrDevPixels[(s-v*w)-u].x;
			}
		    // bras east
		    sum+=ptrDeviceNoyau[ss+v]*ptrDevPixels[s+v].x;
		    // bras west
		    sum+=ptrDeviceNoyau[ss-v]*ptrDevPixels[s-v].x;
		    // bras south
		    sum+=ptrDeviceNoyau[ss+v*k]*ptrDevPixels[s+v*w].x;
		    // bras south
		    sum+=ptrDeviceNoyau[ss-v*k]*ptrDevPixels[s-v*w].x;
		    }
		// centre
		sum+=ptrDeviceNoyau[ss]*ptrDevPixels[s].x;
		ptrColor->x = sum;
		ptrColor->y = sum;
		ptrColor->z = sum;
		}
	    else if(i == h)
		{
		levelGris = 0;
		}
	    }

	__device__
	void lastLine(uchar4* ptrColor, uchar4* ptrDevPixels, float* ptrDeviceNoyau, unsigned char& levelGris, int i, int h, int s)
	    {
	    if(i==0)
		{
		levelGris = 0;
		}
	    else if(i>0 && i<h)
		{
		levelGris = 0;
		}
	    else if(i == h)
		{
		levelGris = 0;
		}
	    }

	__device__
	void f(uchar4* ptrColor, uchar4* ptrDevPixels, float* ptrDeviceNoyau, int k, unsigned char& levelGris, int i, int j, int s, float t)
	    {
	    if(j==0)
		{
		firstLine(ptrColor,ptrDevPixels,ptrDeviceNoyau,levelGris,i,h,s);
		}
	    else if(j>0 && j<w)
		{
		middleLines(ptrColor,ptrDevPixels,ptrDeviceNoyau,k,levelGris,i,j,h,s);
		}
	    else if(j == w)
		{
		lastLine(ptrColor,ptrDevPixels,ptrDeviceNoyau,levelGris,i,h,s);
		}
	    }

	/*--------------------------------------*\
	|*		Attributs		*|
	 \*-------------------------------------*/

    private:
	int w;
	int h;

    };

#endif 

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/

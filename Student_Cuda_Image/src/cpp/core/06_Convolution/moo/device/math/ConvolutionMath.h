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
	void firstLine(uchar4* ptrColor, uchar4* ptrDevPixels, float* ptrDeviceNoyau, int k, unsigned char& levelGris, int i, int h, int s)
	    {
	int k2 = k/2;
	if(i<k2)
	    {
	    levelGris = 0;
	    }
	else if(i>=k2 && i<h-k2)
	    {
	    levelGris = 0;
	    }
	else if(i >= h-k2)
	    {
	    levelGris = 0;
	    }
	    }

	/*
	 *
	 *
	 *
	 */
	__device__
	void middleLines(uchar4* ptrColor, uchar4* ptrDevPixels, float* ptrDeviceNoyau, int k, unsigned char& levelGris, int i, int j, int h, int s)
	    {
	    int ss = (int)(k*((float)k/2.0f));
	    int k2 = k/2;
	    if(i<k2)
		{
		levelGris = 0;
		}
	    else if(i>=k2 && i<h-k2)
		{
		float sum = 0.0f;
		for(int v = 1;v<=k2;v++)
		    {
		    for(int u = 1;u<=k2;u++)
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
	    else if(i >= h-k2)
		{
		levelGris = 0;
		}
	    }

	__device__
	void lastLine(uchar4* ptrColor, uchar4* ptrDevPixels, float* ptrDeviceNoyau, int k, unsigned char& levelGris, int i, int h, int s)
	    {
	    int k2 = k/2;
	    if(i<k2)
		{
		levelGris = 0;
		}
	    else if(i>=k2 && i<h-k2)
		{
		levelGris = 0;
		}
	    else if(i >= h-k2)
		{
		levelGris = 0;
		}
	    }

	__device__
	void f(uchar4* ptrColor, uchar4* ptrDevPixels, float* ptrDeviceNoyau, int k, unsigned char& levelGris, int i, int j, int s, float t)
	    {
	    int k2 = k/2;
	    if(j<k2)
		{
		firstLine(ptrColor,ptrDevPixels,ptrDeviceNoyau,k,levelGris,i,h,s);
		}
	    else if(j>=k/2 && j<w-k2)
		{
		middleLines(ptrColor,ptrDevPixels,ptrDeviceNoyau,k,levelGris,i,j,h,s);
		}
	    else if(j >= w-k2)
		{
		lastLine(ptrColor,ptrDevPixels,ptrDeviceNoyau,k,levelGris,i,h,s);
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

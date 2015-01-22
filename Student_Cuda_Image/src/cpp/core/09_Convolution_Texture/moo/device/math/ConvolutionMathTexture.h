#ifndef CONVOLUTIONMATHTEXTURE_H_
#define CONVOLUTIONMATHTEXTURE_H_

#include "MathTools.h"
#include <cstdio>

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

class ConvolutionMathTexture
    {

	/*--------------------------------------*\
	|*		Constructor		*|
	 \*-------------------------------------*/

    public:

	__device__ ConvolutionMathTexture(int w, int h)
	    {
	this->w = w;
	this->h = h;
	    }

	__device__ ConvolutionMathTexture(const ConvolutionMathTexture& source)
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
	void colorIJ(uchar4* ptrColor, uchar4* ptrDevPixels, float* ptrDeviceNoyau, int k, int i, int j, int s)
	    {

	f(ptrColor, ptrDevPixels, ptrDeviceNoyau,k,i, j, s); // update levelGris

	ptrColor->w = 255; // opaque
	    }

    private:

	__device__
	void firstLine(uchar4* ptrColor, uchar4* ptrDevPixels, float* ptrDeviceNoyau, int k, int i, int j, int s)
	    {
	int ss = (int)(k*((float)k/2.0f));
	int k2 = k/2;
	if(j<k2)
	    {
	    float sum = 0.0f;

	    for(int v = 1;v<=k2;v++)
		{
		for(int u = 1;u<=k2;u++)
		    {
		    // bas droite
		    sum+=ptrDeviceNoyau[(ss+v*k)+u]*ptrDevPixels[(s+v*w)+u].x;
		    // haut droite
		    if((s-v*w) > 0)
			sum+=ptrDeviceNoyau[(ss-v*k)+u]*ptrDevPixels[(s-v*w)+u].x;
		    else
			sum+=ptrDeviceNoyau[ss]*ptrDevPixels[s].x;
		    // bas gauche
		    if((s-u)%w < k2 && (s+v*w)-u > 0)
			sum+=ptrDeviceNoyau[(ss+v*k)-u]*ptrDevPixels[(s+v*w)-u].x;
		    else
			sum+=ptrDeviceNoyau[ss]*ptrDevPixels[s].x;
		    // haut gauche
		    if((s-v*w)>0 && (s-u)%w < k2)
			sum+=ptrDeviceNoyau[(ss-v*k)-u]*ptrDevPixels[(s-v*w)-u].x;
		    else
			sum+=ptrDeviceNoyau[ss]*ptrDevPixels[s].x;
		    }
		// bras east
		sum+=ptrDeviceNoyau[ss+v]*ptrDevPixels[s+v].x;
		// bras west
		if((s-v)%w < k2 && s-v > 0)
		    sum+=ptrDeviceNoyau[ss-v]*ptrDevPixels[s-v].x;
		else
		    sum+=ptrDeviceNoyau[ss]*ptrDevPixels[s].x;
		// bras south
		sum+=ptrDeviceNoyau[ss+v*k]*ptrDevPixels[s+v*w].x;
		// bras north
		if(s-v*w > 0)
		    sum+=ptrDeviceNoyau[ss-v*k]*ptrDevPixels[s-v*w].x;
		else
		    sum+=ptrDeviceNoyau[ss]*ptrDevPixels[s].x;
		}
	    // centre
	    sum+=ptrDeviceNoyau[ss]*ptrDevPixels[s].x;
	    ptrColor->x = sum;
	    ptrColor->y = sum;
	    ptrColor->z = sum;
	    }
	else if(j>=k2 && j<w-k2)
	    {
	    float sum = 0.0f;

	    for(int v = 1;v<=k2;v++)
		{
		for(int u = 1;u<=k2;u++)
		    {
		    // bas droite
		    sum+=ptrDeviceNoyau[(ss+v*k)+u]*ptrDevPixels[(s+v*w)+u].x;
		    // haut droite
		    if((s-v*w) > 0)
			sum+=ptrDeviceNoyau[(ss-v*k)+u]*ptrDevPixels[(s-v*w)+u].x;
		    else
			sum+=ptrDeviceNoyau[ss]*ptrDevPixels[s].x;
		    // bas gauche
		    sum+=ptrDeviceNoyau[(ss+v*k)-u]*ptrDevPixels[(s+v*w)-u].x;
		    // haut gauche
		    if((s-v*w)>0)
			sum+=ptrDeviceNoyau[(ss-v*k)-u]*ptrDevPixels[(s-v*w)-u].x;
		    else
			sum+=ptrDeviceNoyau[ss]*ptrDevPixels[s].x;
		    }
		// bras east
		sum+=ptrDeviceNoyau[ss+v]*ptrDevPixels[s+v].x;
		// bras west
		sum+=ptrDeviceNoyau[ss-v]*ptrDevPixels[s-v].x;
		// bras south
		sum+=ptrDeviceNoyau[ss+v*k]*ptrDevPixels[s+v*w].x;
		// bras north
		if(s-v*w > 0)
		    sum+=ptrDeviceNoyau[ss-v*k]*ptrDevPixels[s-v*w].x;
		else
		    sum+=ptrDeviceNoyau[ss]*ptrDevPixels[s].x;
		}
	    // centre
	    sum+=ptrDeviceNoyau[ss]*ptrDevPixels[s].x;
	    ptrColor->x = sum;
	    ptrColor->y = sum;
	    ptrColor->z = sum;
	    }
	else if(j >= w-k2)
	    {
	    float sum = 0.0f;

	    for(int v = 1;v<=k2;v++)
		{
		for(int u = 1;u<=k2;u++)
		    {
		    // bas droite
		    if((s%w)+u<w)
			sum+=ptrDeviceNoyau[(ss+v*k)+u]*ptrDevPixels[(s+v*w)+u].x;
		    // haut droite
		    if((s-v*w) > 0 && (s%w)+u<w)
			sum+=ptrDeviceNoyau[(ss-v*k)+u]*ptrDevPixels[(s-v*w)+u].x;
		    else
			sum+=ptrDeviceNoyau[ss]*ptrDevPixels[s].x;
		    // bas gauche
		    sum+=ptrDeviceNoyau[(ss+v*k)-u]*ptrDevPixels[(s+v*w)-u].x;
		    // haut gauche
		    if((s-v*w)>0)
			sum+=ptrDeviceNoyau[(ss-v*k)-u]*ptrDevPixels[(s-v*w)-u].x;
		    else
			sum+=ptrDeviceNoyau[ss]*ptrDevPixels[s].x;
		    }
		// bras east
		if((s%w)+v < w)
		    sum+=ptrDeviceNoyau[ss+v]*ptrDevPixels[s+v].x;
		else
		    sum+=ptrDeviceNoyau[ss]*ptrDevPixels[s].x;
		// bras west
		sum+=ptrDeviceNoyau[ss-v]*ptrDevPixels[s-v].x;
		// bras south
		sum+=ptrDeviceNoyau[ss+v*k]*ptrDevPixels[s+v*w].x;
		// bras north
		if(s-v*w > 0)
		    sum+=ptrDeviceNoyau[ss-v*k]*ptrDevPixels[s-v*w].x;
		else
		    sum+=ptrDeviceNoyau[ss]*ptrDevPixels[s].x;
		}
	    // centre
	    sum+=ptrDeviceNoyau[ss]*ptrDevPixels[s].x;
	    ptrColor->x = sum;
	    ptrColor->y = sum;
	    ptrColor->z = sum;
	    }
	    }

	/*
	 *
	 *
	 *
	 */
	__device__
	void middleLines(uchar4* ptrColor, uchar4* ptrDevPixels, float* ptrDeviceNoyau, int k, int i, int j, int s)
	    {
	    int ss = (int)(k*((float)k/2.0f));
	    int k2 = k/2;
	    if(j<k2)
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
			if((s+v*w)-u>0)
			    sum+=ptrDeviceNoyau[(ss+v*k)-u]*ptrDevPixels[(s+v*w)-u].x;
			else
			    sum+=ptrDeviceNoyau[ss]*ptrDevPixels[s].x;
			// haut gauche
			if((s-v*w)-u>0)
			    sum+=ptrDeviceNoyau[(ss-v*k)-u]*ptrDevPixels[(s-v*w)-u].x;
			else
			    sum+=ptrDeviceNoyau[ss]*ptrDevPixels[s].x;
			}
		    // bras east
		    sum+=ptrDeviceNoyau[ss+v]*ptrDevPixels[s+v].x;
		    // bras west
		    if(ss-v > 0)
			sum+=ptrDeviceNoyau[ss-v]*ptrDevPixels[s-v].x;
		    else
			sum+=ptrDeviceNoyau[ss]*ptrDevPixels[s].x;
		    // bras south
		    sum+=ptrDeviceNoyau[ss+v*k]*ptrDevPixels[s+v*w].x;
		    // bras north
		    sum+=ptrDeviceNoyau[ss-v*k]*ptrDevPixels[s-v*w].x;
		    }
		// centre
		sum+=ptrDeviceNoyau[ss]*ptrDevPixels[s].x;
		ptrColor->x = sum;
		ptrColor->y = sum;
		ptrColor->z = sum;
		}
	    else if(j>=k2 && j<w-k2)
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
	    else if(j >= w-k2)
		{
		float sum = 0.0f;

		for(int v = 1;v<=k2;v++)
		    {
		    for(int u = 1;u<=k2;u++)
			{
			// bas droite
			if((s%w)+u<w)
			    sum+=ptrDeviceNoyau[(ss+v*k)+u]*ptrDevPixels[(s+v*w)+u].x;
			else
			    sum+=ptrDeviceNoyau[ss]*ptrDevPixels[s].x;
			// haut droite
			if((s%w)+u<w)
			    sum+=ptrDeviceNoyau[(ss-v*k)+u]*ptrDevPixels[(s-v*w)+u].x;
			else
			    sum+=ptrDeviceNoyau[ss]*ptrDevPixels[s].x;
			// bas gauche
			sum+=ptrDeviceNoyau[(ss+v*k)-u]*ptrDevPixels[(s+v*w)-u].x;
			// haut gauche
			sum+=ptrDeviceNoyau[(ss-v*k)-u]*ptrDevPixels[(s-v*w)-u].x;
			}
		    // bras east
		    if((s%w)+v < w)
			sum+=ptrDeviceNoyau[ss+v]*ptrDevPixels[s+v].x;
		    else
			sum+=ptrDeviceNoyau[ss]*ptrDevPixels[s].x;
		    // bras west
		    sum+=ptrDeviceNoyau[ss-v]*ptrDevPixels[s-v].x;
		    // bras south
		    sum+=ptrDeviceNoyau[ss+v*k]*ptrDevPixels[s+v*w].x;
		    // bras north
		    sum+=ptrDeviceNoyau[ss-v*k]*ptrDevPixels[s-v*w].x;
		    }
		// centre
		sum+=ptrDeviceNoyau[ss]*ptrDevPixels[s].x;
		ptrColor->x = sum;
		ptrColor->y = sum;
		ptrColor->z = sum;
		}
	    }

	__device__
	void lastLine(uchar4* ptrColor, uchar4* ptrDevPixels, float* ptrDeviceNoyau, int k, int i, int j, int s)
	    {
	    int ss = (int)(k*((float)k/2.0f));
	    int k2 = k/2;
	    if(j<k2)
		{
		float sum = 0.0f;

		for(int v = 1;v<=k2;v++)
		    {
		    for(int u = 1;u<=k2;u++)
			{
			// bas droite
			if(s+v*w < w*h)
			    sum+=ptrDeviceNoyau[(ss+v*k)+u]*ptrDevPixels[(s+v*w)+u].x;
			else
			    sum+=ptrDeviceNoyau[ss]*ptrDevPixels[s].x;
			// haut droite
			sum+=ptrDeviceNoyau[(ss-v*k)+u]*ptrDevPixels[(s-v*w)+u].x;
			// bas gauche
			if((s+v*w)<w*h && (s-u)%w < k2)
			    sum+=ptrDeviceNoyau[(ss+v*k)-u]*ptrDevPixels[(s+v*w)-u].x;
			else
			    sum+=ptrDeviceNoyau[ss]*ptrDevPixels[s].x;
			// haut gauche
			if((s-u)%w<k2)
			    sum+=ptrDeviceNoyau[(ss-v*k)-u]*ptrDevPixels[(s-v*w)-u].x;
			else
			    sum+=ptrDeviceNoyau[ss]*ptrDevPixels[s].x;
			}
		    // bras east
		    sum+=ptrDeviceNoyau[ss+v]*ptrDevPixels[s+v].x;
		    // bras west
		    if((s-v)%w < k2)
			sum+=ptrDeviceNoyau[ss-v]*ptrDevPixels[s-v].x;
		    else
			sum+=ptrDeviceNoyau[ss]*ptrDevPixels[s].x;
		    // bras south
		    if(s+v*w < w*h)
			sum+=ptrDeviceNoyau[ss+v*k]*ptrDevPixels[s+v*w].x;
		    else
			sum+=ptrDeviceNoyau[ss]*ptrDevPixels[s].x;
		    // bras north
		    sum+=ptrDeviceNoyau[ss-v*k]*ptrDevPixels[s-v*w].x;
		    }
		// centre
		sum+=ptrDeviceNoyau[ss]*ptrDevPixels[s].x;
		ptrColor->x = sum;
		ptrColor->y = sum;
		ptrColor->z = sum;
		}
	    else if(j>=k2 && j<w-k2)
		{
		float sum = 0.0f;

		for(int v = 1;v<=k2;v++)
		    {
		    for(int u = 1;u<=k2;u++)
			{
			// bas droite
			if((s+v*w)<w*h)
			    sum+=ptrDeviceNoyau[(ss+v*k)+u]*ptrDevPixels[(s+v*w)+u].x;
			else
			    sum+=ptrDeviceNoyau[ss]*ptrDevPixels[s].x;
			// haut droite
			sum+=ptrDeviceNoyau[(ss-v*k)+u]*ptrDevPixels[(s-v*w)+u].x;
			// bas gauche
			if((s+v*w)<w*h)
			    sum+=ptrDeviceNoyau[(ss+v*k)-u]*ptrDevPixels[(s+v*w)-u].x;
			else
			    sum+=ptrDeviceNoyau[ss]*ptrDevPixels[s].x;
			// haut gauche
			sum+=ptrDeviceNoyau[(ss-v*k)-u]*ptrDevPixels[(s-v*w)-u].x;
			}
		    // bras east
		    sum+=ptrDeviceNoyau[ss+v]*ptrDevPixels[s+v].x;
		    // bras west
		    sum+=ptrDeviceNoyau[ss-v]*ptrDevPixels[s-v].x;
		    // bras south
		    if(s+v*w < w*h)
			sum+=ptrDeviceNoyau[ss+v*k]*ptrDevPixels[s+v*w].x;
		    else
			sum+=ptrDeviceNoyau[ss]*ptrDevPixels[s].x;
		    // bras north
		    sum+=ptrDeviceNoyau[ss-v*k]*ptrDevPixels[s-v*w].x;
		    }
		// centre
		sum+=ptrDeviceNoyau[ss]*ptrDevPixels[s].x;
		ptrColor->x = sum;
		ptrColor->y = sum;
		ptrColor->z = sum;
		}
	    else if(j >= w-k2)
		{
		float sum = 0.0f;

		for(int v = 1;v<=k2;v++)
		    {
		    for(int u = 1;u<=k2;u++)
			{
			// bas droite
			if((s+v*w)<w*h && (s%w)+u<w)
			    sum+=ptrDeviceNoyau[(ss+v*k)+u]*ptrDevPixels[(s+v*w)+u].x;
			else
			    sum+=ptrDeviceNoyau[ss]*ptrDevPixels[s].x;
			// haut droite
			if((s%w)+u<w)
			    sum+=ptrDeviceNoyau[(ss-v*k)+u]*ptrDevPixels[(s-v*w)+u].x;
			else
			    sum+=ptrDeviceNoyau[ss]*ptrDevPixels[s].x;
			// bas gauche
			if((s+v*w)<w*h)
			    sum+=ptrDeviceNoyau[(ss+v*k)-u]*ptrDevPixels[(s+v*w)-u].x;
			else
			    sum+=ptrDeviceNoyau[ss]*ptrDevPixels[s].x;
			// haut gauche
			sum+=ptrDeviceNoyau[(ss-v*k)-u]*ptrDevPixels[(s-v*w)-u].x;
			}
		    // bras east
		    if((s%w)+v < w)
			sum+=ptrDeviceNoyau[ss+v]*ptrDevPixels[s+v].x;
		    else
			sum+=ptrDeviceNoyau[ss]*ptrDevPixels[s].x;
		    // bras west
		    sum+=ptrDeviceNoyau[ss-v]*ptrDevPixels[s-v].x;
		    // bras south
		    if(s+v*w < w*h)
			sum+=ptrDeviceNoyau[ss+v*k]*ptrDevPixels[s+v*w].x;
		    else
			sum+=ptrDeviceNoyau[ss]*ptrDevPixels[s].x;
		    // bras north
		    sum+=ptrDeviceNoyau[ss-v*k]*ptrDevPixels[s-v*w].x;
		    }
		// centre
		sum+=ptrDeviceNoyau[ss]*ptrDevPixels[s].x;
		ptrColor->x = sum;
		ptrColor->y = sum;
		ptrColor->z = sum;
		}
	    }

	__device__
	void f(uchar4* ptrColor, uchar4* ptrDevPixels, float* ptrDeviceNoyau, int k, int i, int j, int s)
	    {
	    int k2 = k/2;
	    if(i<k2)
		{
		firstLine(ptrColor,ptrDevPixels,ptrDeviceNoyau,k,i,j,s);
		}
	    else if(i>=k2 && i<h-k2)
		{
		middleLines(ptrColor,ptrDevPixels,ptrDeviceNoyau,k,i,j,s);
		}
	    else if(i>=h-k2)
		{
		lastLine(ptrColor,ptrDevPixels,ptrDeviceNoyau,k,i,j,s);
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

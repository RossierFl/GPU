#ifndef CONVOLUTION_MATH_H_
#define CONVOLUTION_MATH_H_

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/
#include "cudaType.h"
#include <math.h>
/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

/**
 * Dans un header only pour preparer la version cuda
 */
class ConvolutionMath
        {

	/*--------------------------------------*\
	|*		Constructor		*|
	 \*-------------------------------------*/

    public:

	 ConvolutionMath(int w, int h)
	    {
	this->w = w;
	this->h = h;
	    }

	 ConvolutionMath(const ConvolutionMath& source)
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

	void colorIJ(uchar4* ptrColor, uchar4* ptrDevPixels, float* ptrDeviceNoyau, int k, int i, int j, int s)
	    {

	f(ptrColor, ptrDevPixels, ptrDeviceNoyau,k,i, j, s); // update levelGris

	//	ptrOutputColor->x = levelGris;
	//	ptrOutputColor->y = levelGris;
	//	ptrOutputColor->z = levelGris;
	// trololololo

	ptrColor->w = 255; // opaque
	    }

    private:


	void firstLine(uchar4* ptrColor, uchar4* ptrDevPixels, float* ptrDeviceNoyau, int k, int i, int j, int s)
	    {
	int k2 = k/2;
	if(j<k2)
	    {
	    ptrColor->x = 0;
	    ptrColor->y = 0;
	    ptrColor->z = 0;
	    }
	else if(j>=k2 && j<w-k2)
	    {
	    ptrColor->x = 0;
	    ptrColor->y = 0;
	    ptrColor->z = 0;
	    }
	else if(j >= w-k2)
	    {
	    ptrColor->x = 0;
	    ptrColor->y = 0;
	    ptrColor->z = 0;
	    }
	    }

	/*
	 *
	 *
	 *
	 */

	void middleLines(uchar4* ptrColor, uchar4* ptrDevPixels, float* ptrDeviceNoyau, int k, int i, int j, int s)
	    {
	    int ss = (int)(k*((float)k/2.0f));
	    int k2 = k/2;
	    if(j<k2)
		{
		ptrColor->x = 0;
		ptrColor->y = 0;
		ptrColor->z = 0;
		}
	    else if(j>=k2 && j<w-k2)
		{
		//		ptrColor->x = 0;
		//		ptrColor->y = 0;
		//		ptrColor->z = 0;
		//		return;
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
		ptrColor->x = 0;
		ptrColor->y = 0;
		ptrColor->z = 0;
		}
	    }


	void lastLine(uchar4* ptrColor, uchar4* ptrDevPixels, float* ptrDeviceNoyau, int k, int i, int j, int s)
	    {
	    int k2 = k/2;
	    if(j<k2)
		{
		ptrColor->x = 0;
		ptrColor->y = 0;
		ptrColor->z = 0;
		}
	    else if(j>=k2 && j<w-k2)
		{
		ptrColor->x = 0;
		ptrColor->y = 0;
		ptrColor->z = 0;
		}
	    else if(j >= w-k2)
		{
		ptrColor->x = 0;
		ptrColor->y = 0;
		ptrColor->z = 0;
		}
	    }


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
    private :
	int w;
	int h;



        };
#endif

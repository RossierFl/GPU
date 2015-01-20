#ifndef CONVOLUTION_TEXTURE_MATH_H_
#define CONVOLUTION_TEXTURE_MATH_H_

#include "MathTools.h"
#include <cstdio>

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/
extern __device__ void getTextureMem(uchar4* ptrPixel,int j,int i);
class ConvolutionTextureMath
    {

	/*--------------------------------------*\
	|*		Constructor		*|
	 \*-------------------------------------*/

    public:

	__device__ ConvolutionTextureMath(int w, int h)
	    {
	this->w = w;
	this->h = h;
	    }

	__device__ ConvolutionTextureMath(const ConvolutionTextureMath& source)
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
	/*__device__
	void colorIJ(uchar4* ptrColor, uchar4* ptrDevPixels, float* ptrDeviceNoyau, int k, int i, int j, int s)
	    {

	f(ptrColor, ptrDevPixels, ptrDeviceNoyau,k,i, j, s); // update levelGris

	//	ptrOutputColor->x = levelGris;
	//	ptrOutputColor->y = levelGris;
	//	ptrOutputColor->z = levelGris;
	// trololololo

	ptrColor->w = 255; // opaque
	    }*/

	__device__
	void colorIJ(uchar4* ptrColor, float* ptrDeviceNoyau, size_t dimKernel,int w,int pixelJ,int pixelI){
	    size_t size = dimKernel* dimKernel;
	    int kernOffset= -dimKernel/2;
	    int sum = 0;
		/*for(int s=0;s<size;s++){
		    sum += ptrVideoImage[s].x * ptrDeviceNoyau[s];
		}*/

		int sk=0;
			for(int i=0;i<dimKernel;i++){
			    int iTex = kernOffset+i;
			    for (int j=0;j<dimKernel;j++){
				int jTex=kernOffset+j;
				uchar4 pix;
				getTextureMem(&pix,jTex+pixelJ,iTex+pixelI);
				sum+=ptrDeviceNoyau[sk] *pix.x;
				//sum+=ptrDeviceNoyau[sk] *tex2D(textureRef,jTex+pixelJ,iTex+pixelI).x;

			    sk++;
			    }
			}

		ptrColor->x=sum;
		ptrColor->y=sum;
		ptrColor->z=sum;
		ptrColor->w=255;
		/*ptrColor->x=255;
		ptrColor->y=255;
		ptrColor->z=255;*/




	}

    private:

	__device__
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
	__device__
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

	__device__
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

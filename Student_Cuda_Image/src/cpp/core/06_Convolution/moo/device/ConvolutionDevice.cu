#include "Indice2D.h"
#include "IndiceTools.h"
#include "cudaTools.h"
#include "Device.h"

#include "ConvolutionMath.h"

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

__global__ void convolutionKernel(uchar4* ptrDevPixels, float* ptrDeviceNoyau, int k, int w, int h,float t);

__global__ void colorToGrey(uchar4* ptrDevPixels, int w, int h);

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

/*----------------------------------------------------------------------*\
 |*			Implementation 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

__global__ void colorToGrey(uchar4* ptrDevPixels, int w, int h)
    {
    const int TID = Indice2D::tid();
    const int NB_THREAD = Indice2D::nbThread();

    const int WH=w*h;

    int s = TID;
    while(s<WH)
	{
	float x = ptrDevPixels[s].x;
	float y = ptrDevPixels[s].y;
	float z = ptrDevPixels[s].z;
	float average = (x/(float)3.0+y/(float)3.0+z/(float)3.0);
	ptrDevPixels[s].x = average;
	ptrDevPixels[s].y = average;
	ptrDevPixels[s].z = average;
	ptrDevPixels[s].w = 255;
	s += NB_THREAD;
	}
    }

__global__ void convolutionKernel(uchar4* ptrDevPixels, float* ptrDeviceNoyau, int k, int w, int h, float t)
    {
    ConvolutionMath convMath = ConvolutionMath(w, h);

    const int TID = Indice2D::tid();
    const int NB_THREAD = Indice2D::nbThread();

    const int WH=w*h;

    uchar4 color;

    int pixelI;
    int pixelJ;

    int s = TID;
    while (s < WH)
	{
	IndiceTools::toIJ(s, w, &pixelI, &pixelJ); // update (pixelI, pixelJ)
	color = ptrDevPixels[s];
	convMath.colorIJ(&color,ptrDevPixels,ptrDeviceNoyau,k,pixelI, pixelJ, s, t); 	// update color
	ptrDevPixels[s] = color;

	s += NB_THREAD;
	}
    }

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/


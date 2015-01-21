/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/
#include "ConvolutionDevice.h"
#include <iostream>
#include <omp.h>
#include "IndiceTools.h"
#include "OmpTools.h"

void ConvolutionDevice::ecrasementTexture(uchar* tabSM, int halfThread)
    {
    const int TID_LOCAL = Indice1D::tidLocalBlock();
    const int NB_THREAD_BLOCK = Indice1D::nbThreadBlock();
    int s = TID_LOCAL;
    while (s < halfThread)
	{
	if (tabSM[s] > tabSM[s + halfThread]) // if tabSM not min
	    tabSM[s] = tabSM[s + halfThread];
	if (tabSM[NB_THREAD_BLOCK + s] < tabSM[NB_THREAD_BLOCK + s + halfThread]) // if tabSM not max
	    tabSM[NB_THREAD_BLOCK + s] = tabSM[NB_THREAD_BLOCK + s + halfThread];
	s += NB_THREAD_BLOCK;
	}
    }

void ConvolutionDevice::reductionIntraBTexture(uchar* tabSM)
    {
    const int NB_THREAD = Indice1D::nbThread();
    const int NB_THREAD_BLOCK = Indice1D::nbThreadBlock();
    int halfThread = NB_THREAD_BLOCK / 2;
    while (halfThread >= 1)
	{
	ecrasementTexture(tabSM, halfThread);
	__syncthreads();
	halfThread /= 2;
	}
    }

void ConvolutionDevice::reductionInterBTexture(uchar* tabSM, uchar* ptrDevResult)
    {
    const int TID_LOCAL = Indice1D::tidLocalBlock();
    const int NB_THREADS = Indice1D::nbThreadBlock();
    const int NB_BLOCKS = gridDim.x;
    const int BID = blockIdx.x;
    if (TID_LOCAL == 0)
	{
	// bad idea with Lock, finish on CPU instead, only NB_BLOCKS items
	ptrDevResult[BID] = tabSM[0]; // min
	ptrDevResult[NB_BLOCKS + BID] = tabSM[NB_THREADS]; // max
	}

    }

void ConvolutionDevice::reductionIntraTTexture(uchar* tabSM, uchar4* ptrDevPixels, int n)
    {
    const int NB_THREAD = Indice1D::nbThread();
    const int TID = Indice1D::tid();
    const int TID_LOCAL = Indice1D::tidLocalBlock();

    int s = TID;
    uchar minCrtThread = 255;
    uchar maxCrtThread = 0;
    while (s < n)
	{
	uchar crtVal = ptrDevPixels[s].x;
	if (crtVal > maxCrtThread)
	    maxCrtThread = crtVal;
	if (crtVal < minCrtThread)
	    minCrtThread = crtVal;
	s += NB_THREAD;
	}
    tabSM[TID_LOCAL] = minCrtThread;
    tabSM[Indice1D::nbThreadBlock() + TID_LOCAL] = maxCrtThread; // tabSM is 2*n size
    }

void ConvolutionDevice::colorToGreyTexture(uchar4* ptrDevPixels, int w, int h)
    {
    const int TID = OmpTools::getTid();
    const int NB_THREAD = OmpTools::getNbThread();

    const int WH = w * h;

    int s = TID;
    while (s < WH)
	{

	float x = ptrDevPixels[s].x;
	float y = ptrDevPixels[s].y;
	float z = ptrDevPixels[s].z;
	float average = (x / (float) 3.0 + y / (float) 3.0 + z / (float) 3.0);
	ptrDevPixels[s].x = average;
	ptrDevPixels[s].y = average;
	ptrDevPixels[s].z = average;
	ptrDevPixels[s].w = 255;
	s += NB_THREAD;
	}
    }

void ConvolutionDevice::affineTransformTexture(uchar4* ptrDevPixels, float a, float b, int w, int h, int offset)
    {
    const int TID = OmpTools::getTid();
     const int NB_THREAD = OmpTools::getNbThread();

    const int WH = w * h;

    int s = TID;
    while (s < WH)
	{
	uchar newValue = (uchar)((float) (ptrDevPixels[s].x) * a + b);
	newValue += offset;
	if (newValue > 255)
	    newValue = 255;
	ptrDevPixels[s].x = newValue;
	ptrDevPixels[s].y = newValue;
	ptrDevPixels[s].z = newValue;
	s += NB_THREAD;
	}
    }

void ConvolutionDevice::convolutionTextureKernel(uchar4* ptrDevPixels, int k, int w, int h, float t)
    {
    ConvolutionTextureMath convMath = ConvolutionTextureMath(w, h);

    const int TID = OmpTools::getTid();
     const int NB_THREAD = OmpTools::getNbThread();

    const int WH = w * h;

    uchar4 color;

    int pixelI;
    int pixelJ;

    int s = TID;
    while (s < WH)
	{
	IndiceTools::toIJ(s, w, &pixelI, &pixelJ); // update (pixelI, pixelJ)
	const int KERN_SIZE = 9;

	convMath.colorIJ(&color, CONST_MEM_KERNEL, KERN_SIZE, w, pixelJ, pixelI); // update color
	ptrDevPixels[s] = color;
	s += NB_THREAD;
	}
    }

/*
 * ptrDevResult should contain min in [0] and max in [1]
 */
void ConvolutionDevice::findMinMaxTexture(uchar4* ptrDevPixels, uchar* ptrDevResult, int w, int h)
    {
    // one shared memory per block
    extern __shared__ uchar
    tabSM[];
    //const int TID_LOCAL = Indice1D::tidLocalBlock();

    int sizePtrDevPixels = w * h;
    reductionIntraTTexture(tabSM, ptrDevPixels, sizePtrDevPixels);
    reductionIntraBTexture (tabSM);
    reductionInterBTexture(tabSM, ptrDevResult);
    }

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/


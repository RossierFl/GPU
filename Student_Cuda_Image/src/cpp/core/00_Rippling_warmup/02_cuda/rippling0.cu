#include <iostream>
#include <stdlib.h>

#include "Indice2D.h"
#include "IndiceTools.h"
#include "cudaTools.h"
#include "Device.h"

#include "Rippling0Math.h"

using std::cout;
using std::endl;

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Imported	 	*|
 \*-------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/



/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

static __global__ void rippling0(uchar4* ptrDevPixels,int w, int h,float t);

/*----------------------------------------------------------------------*\
 |*			Implementation 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

void launchKernelRippling0(uchar4* ptrDevPixels, int w, int h, float t)
    {
    dim3 dg = dim3(8, 8, 1); // disons, a optimiser
    dim3 db = dim3(16, 16, 1); // disons, a optimiser

    //Device::print(dg, db);
     Device::checkDimError(dg,db);

    rippling0<<<dg,db>>>(ptrDevPixels,w,h,t);
    Device::checkKernelError("rippling0");
    }

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

__global__ void rippling0(uchar4* ptrDevPixels, int w, int h, float t)
    {
    Rippling0Math rippling0Math = Rippling0Math(w, h);

    const int TID = Indice2D::tid();
    const int NB_THREAD = Indice2D::nbThread();

    const int WH=w*h;

    uchar4 color;
    color.w = 255; // alpha

    int pixelI;
    int pixelJ;

    int s = TID;
    while (s < WH)
	{
	IndiceTools::toIJ(s, w, &pixelI, &pixelJ); // update (pixelI, pixelJ)

	rippling0Math.color(pixelI, pixelJ, t, &color); // update color
	ptrDevPixels[s] = color;

	s += NB_THREAD;
	}

    }



/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/


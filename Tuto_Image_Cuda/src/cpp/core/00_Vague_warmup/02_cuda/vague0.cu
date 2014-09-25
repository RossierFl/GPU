#include <iostream>
#include <stdlib.h>

#include "Indice2D.h"
#include "IndiceTools.h"
#include "cudaTools.h"
#include "Device.h"

#include "Vague0Math.h"

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

static __global__ void vague0(uchar4* ptrDevPixels,int w, int h,float t);

/*----------------------------------------------------------------------*\
 |*			Implementation 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

void launchKernelVague0(uchar4* ptrDevPixels, int w, int h, float t)
    {
    dim3 dg = dim3(8, 8, 1); // disons, a optimiser !!
    dim3 db = dim3(16, 16, 1); // disons, a optimiser !!

    //Device::print(dg, db);
     Device::checkDimError(dg,db);

     vague0<<<dg,db>>>(ptrDevPixels,w,h,t);
    Device::checkKernelError("vague0");
    }

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

__global__ void vague0(uchar4* ptrDevPixels, int w, int h, float t)
    {
    Vague0Math vague0Math = Vague0Math(w, h);

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

	vague0Math.colorIJ(&color,pixelI, pixelJ, t); 	// update color
	ptrDevPixels[s] = color;

	s += NB_THREAD;
	}
    }


/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/


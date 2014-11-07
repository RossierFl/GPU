#include <iostream>

#include "Indice2D.h"
#include "IndiceTools.h"
#include "cudaTools.h"
#include "Device.h"

#include "RipplingMath.h"

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

__global__ void rippling(uchar4* ptrDevPixels, int w, int h, float t);

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

/*----------------------------------------------------------------------*\
 |*			Implementation 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

__global__ void rippling(uchar4* ptrDevPixels, int w, int h, float t)
    {
    RipplingMath ripplingMath = RipplingMath(w, h);

    const int TID = Indice2D::tid();
    const int NB_THREADS = Indice2D::nbThread();
    const int SIZE = w*h;

    int s = TID;
    int i =0;
    int j =0;
    while(s<SIZE){
	IndiceTools::toIJ(s, w, &i, &j); // s[0,W*H[ --> i[0,H[ j[0,W[
	ripplingMath.colorIJ(&ptrDevPixels[s], i, j,t);
	s+=NB_THREADS;
    }
    }

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/


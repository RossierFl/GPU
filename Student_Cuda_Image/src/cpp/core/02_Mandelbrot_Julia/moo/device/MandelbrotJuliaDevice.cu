#include <iostream>

#include "Indice2D.h"
#include "cudaTools.h"
#include "Device.h"

#include "MandelbrotJuliaMath.h"
#include "IndiceTools.h"

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

__global__ void mandelbrotJulia(uchar4* ptrDevPixels,int w, int h, DomaineMath & domaineMath,float t,float cX,float cY,bool isJulia);

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

__global__ void mandelbrotJulia(uchar4* ptrDevPixels,int w, int h, DomaineMath & domaineMath,float t,float cX,float cY,bool isJulia)
    {
    MandelbrotJuliaMath MandelbrotJuliaMath(n,isJulia,cX,cY); // ici pour preparer cuda

    // TODO pattern entrelacement




       const int WH = w * h;


       const int TID = Indice2D::tid();
   	const int NB_THREAD = Indice2D::nbThread();// dans region parallel

   	int s = TID; // in [0,...

   	int i;
   	int j;
   	while (s < WH)
   	    {
   	    IndiceTools::toIJ(s, w, &i, &j); // s[0,W*H[ --> i[0,H[ j[0,W[

   	 // (i,j) domaine ecran dans N2
   	   	    // (x,y) domaine math dans R2

   	   	    double x;
   	   	    double y;

   	   	    domaineMath.toXY(i, j, &x, &y); // fill (x,y) from (i,j)

   	   	   // float t=variateurT.get();
   	   	   // float t=12;
   	   	    ptrMandelbrotJuliaMath->colorXY(ptrColorIJ,x, y, domaineMath,t);

   	    s += NB_THREAD;
   	    }







    }

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/


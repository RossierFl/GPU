#include "Indice2D.h"
#include "IndiceTools.h"
#include "DomaineMath.h"
#include "cudaTools.h"
#include "Device.h"
#include "MandelbrotJuliaMultiGPU.h"
#include "MandelbrotJuliaMathMultiGPU.h"



/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Imported	 	*|
 \*-------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

__global__ void mandelbrotJuliaCuMltiGPU(uchar4* ptrDevPixels,int w, int h,DomaineMath domaineMath, int n,float t,bool isJulia,float cX,float cY,float offset);

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

__global__ void mandelbrotJuliaCuMltiGPU(uchar4* ptrDevPixels, int w, int h, DomaineMath domaineMath, int n, float t,bool isJulia,float cX,float cY,float offset)
    {
    MandelbrotJuliaMultiGPUMath mandelbrotJuliaMath = MandelbrotJuliaMultiGPUMath(n,isJulia,cX,cY);

    const int TID = Indice2D::tid();
    const int NB_THREAD = Indice2D::nbThread();

    const int WH=w*h;

    uchar4 color;

    double x;
    double y;

    int pixelI;
    int pixelJ;

    int s = TID;
    while (s < WH)
	{
	IndiceTools::toIJ(s, w, &pixelI, &pixelJ); // update (pixelI, pixelJ)
	// (i,j) domaine ecran
	// (x,y) domaine math
	domaineMath.toXY(pixelI+offset, pixelJ, &x, &y); //  (i,j) -> (x,y)
	
	mandelbrotJuliaMath.colorXY(&color,x, y,domaineMath,t); // update color

	int newS = IndiceTools::toS(w,pixelI+offset,pixelJ);
	ptrDevPixels[newS] = color;

	s += NB_THREAD;
	}

    }

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/


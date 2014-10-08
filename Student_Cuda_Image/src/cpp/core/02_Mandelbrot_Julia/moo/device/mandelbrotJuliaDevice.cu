#include "Indice2D.h"
#include "IndiceTools.h"
#include "DomaineMath.h"
#include "cudaTools.h"
#include "Device.h"
#include "Fractale.h"
#include "MandelbrotMath.h"
#include "JuliaMath.h"



/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Imported	 	*|
 \*-------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

__global__ void fractale(uchar4* ptrDevPixels, int w, int h, DomaineMath domaineMath, int n, float t,
	int isJulia, double c1, double c2);

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

__global__ void fractale(uchar4* ptrDevPixels, int w, int h, DomaineMath domaineMath, int n, float t,
	int isJulia, double c1, double c2)
    {
    Fractale* fractaleMath = 0;
    if(isJulia)
	fractaleMath = new JuliaMath(n,c1,c2);
    else
	fractaleMath = new MandelbrotMath(n);

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
	domaineMath.toXY(pixelI, pixelJ, &x, &y); //  (i,j) -> (x,y)

	fractaleMath->colorXY(&color,x, y,t); // update color

	ptrDevPixels[s] = color;

	s += NB_THREAD;
	}
    delete fractaleMath;

    }

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/


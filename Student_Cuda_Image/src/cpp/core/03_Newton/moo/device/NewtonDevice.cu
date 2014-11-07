#include "Indice2D.h"
#include "IndiceTools.h"
#include "DomaineMath.h"
#include "cudaTools.h"
#include "Device.h"
#include "NewtonMath.h"

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Imported	 	*|
 \*-------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

__global__ void fractaleNewton(uchar4* ptrDevPixels, int w, int h, DomaineMath domaineMath, float t,
	float eX, float eF, float eX_Star, float* jacobianMat);

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

__global__ void fractaleNewton(uchar4* ptrDevPixels, int w, int h, DomaineMath domaineMath, float t,
	float eX, float eF, float eX_Star,float* jacobianMat)
    {
    NewtonMath* newtonMath = new NewtonMath();

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
	IndiceTools::toIJ(s, w, &pixelI, &pixelJ);
	domaineMath.toXY(pixelI, pixelJ, &x, &y); //  (i,j) -> (x,y)
	newtonMath->colorXY(&color,x, y,t,eX,eF,eX_Star,jacobianMat);
	ptrDevPixels[s] = color;
	s += NB_THREAD;
	}
    delete newtonMath;

    }

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/

#include "Indice2D.h"
#include "IndiceTools.h"
#include "DomaineMath.h"
#include "cudaTools.h"
#include "Device.h"
#include "NewtonMath.h"



/*----------------------------------------------------------------------*\
|*			Declaration 		                            			*|
\*---------------------------------------------------------------------*/

/*--------------------------------------*\
|*		Imported	                	*|
\*--------------------------------------*/

/*--------------------------------------*\
|*		Public			                *|
\*--------------------------------------*/

__global__ void fractalNewton(uchar4* ptrDevPixels, int w, int h, DomaineMath domaineMath, int n, float epsilonx, float epsilonf, float epsilonxstar);

/*--------------------------------------*\
|*		Private		                 	*|
\*--------------------------------------*/

/*----------------------------------------------------------------------*\
|*			Implementation 				                            	*|
\*----------------------------------------------------------------------*/

__global__ void fractalNewton(uchar4* ptrDevPixels, int w, int h, DomaineMath domaineMath, int n, float epsilonx, float epsilonf, float epsilonxstar)
{
	const int TID = Indice2D::tid();
	const int NB_THREAD = Indice2D::nbThread();
	const int WH = w * h;

	uchar4 color;
	double x;
	double y;
	int i;
	int j;
	NewtonMath newtonMath(n);
	int s = TID;
	while (s < WH)
	{
		// Compute (i,j)
		// (i,j) screen domain
		// (x,y) math domain
		IndiceTools::toIJ(s, w, &i, &j);

		// Compute (x,y)
		//  (i,j) -> (x,y)
		domaineMath.toXY(i, j, &x, &y);

		// Compute the color
		newtonMath.colorXY(&color, x, y, epsilonx, epsilonf, epsilonxstar);

		// Apply the color
		ptrDevPixels[s] = color;

		//
		s += NB_THREAD;
	}
}



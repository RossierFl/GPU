#ifndef FRACTALE_H_
#define FRACTALE_H_

#include "CalibreurF.h"
#include "ColorTools.h"
#include <math.h>

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/
class Fractale
    {
    public:

	Fractale(int n) :
	calibreur(IntervalF(0,n), IntervalF(0, 1))
	{
	this->n = n;
	}

	virtual ~Fractale(void)
	    {
	    // rien
	    }

	virtual int indiceArret(double x, double y)=0;

	void colorXY(uchar4* ptrColor, double x, double y, const DomaineMath& domaineMath, double t)
	    {
	    float k = indiceArret(x,y);
	    //printf("%f\n",k);
	    if(k>n)
		{
		ptrColor->x = 0; // noir
		ptrColor->y = 0; // noir
		ptrColor->z = 0; // noir
		}
	    else
		{
		//printf("%f\n",k);
		k = 1.0/(float)n*k;
		//calibreur.calibrer(k);
		ColorTools::HSB_TO_RVB(k, ptrColor); // update color
		}

	    ptrColor->w = 255; // opaque
	    }


	/*--------------------------------------*\
	|*		Attribut		*|
	 \*-------------------------------------*/

    protected:

	// Inputs
	int n;

	// Tools
	CalibreurF calibreur;

    }
;

#endif 

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/

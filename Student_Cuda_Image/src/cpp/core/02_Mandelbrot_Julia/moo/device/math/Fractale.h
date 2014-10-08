#ifndef FRACTALE_H_
#define FRACTALE_H_

#include <math.h>

#include "CalibreurF.h"
#include "ColorTools.h"


/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/


class Fractale
    {

	/*--------------------------------------*\
	|*		Constructor		*|
	 \*-------------------------------------*/

    public:

	__device__ Fractale(int n)
	/*:calibreur(IntervalF(0, n), IntervalF(0, 1))*/
	    {
	this->n = n;
	    }

	__device__ virtual ~Fractale(void)
	    {
	    // rien
	    }

	// constructeur copie automatique car pas pointeur dans
	//	DamierMath
	// 	calibreur
	// 	IntervalF

	/*--------------------------------------*\
	|*		Methodes		*|
	 \*-------------------------------------*/

    public:

	__device__
	virtual int indiceArret(double x, double y)=0;

	/**
	 * x=pixelI
	 * y=pixelJ
	 */
	__device__
	void colorXY(uchar4* ptrColor,float x, float y,float t)
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
	|*		Attributs		*|
	 \*-------------------------------------*/

    protected:

	// Input
	int n;

	// Tools
	//CalibreurF calibreur;

    };



#endif 



/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/

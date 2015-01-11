#ifndef HEATTRANSFERTMATH_H_
#define HEATTRANSFERTMATH_H_

#include <math.h>

#include "CalibreurF.h"
#include "ColorTools.h"
#include "IndiceTools.h"


/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/


class HeatTransfertMath
    {

	/*--------------------------------------*\
	|*		Constructor		*|
	 \*-------------------------------------*/

    public:

	__device__ HeatTransfertMath(float n)
	/*:calibreur(IntervalF(0, n), IntervalF(0, 1))*/
	    {
	      this->k = k;
	    }

	__device__ virtual ~HeatTransfertMath(void)
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
	__device__ void getNewPixelValue(float* newPixelValue,float* ptrDevImageA,float k,int s,int w){
	  float valueBase = ptrDevImageA[s];
	  float up = ptrDevImageA[s-w];
	  float back = ptrDevImageA[s-1];
	  float next = ptrDevImageA[s+1];
	  float down = ptrDevImageA[s+w];
	  *newPixelValue = valueBase+k*(up+down+next+back-4*valueBase);
	}

	/*--------------------------------------*\
	|*		Attributs		*|
	 \*-------------------------------------*/

    protected:

	// Input
	float k;


	// Tools
	//CalibreurF calibreur;

    };



#endif 



/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/

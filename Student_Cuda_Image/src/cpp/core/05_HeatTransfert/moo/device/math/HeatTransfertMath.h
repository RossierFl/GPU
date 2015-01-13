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
	    {
	this->k = k;
	    }

	__device__ virtual ~HeatTransfertMath(void)
	    {
	    // rien
	    }

	/*--------------------------------------*\
	|*		Methodes		*|
	 \*-------------------------------------*/

    public:
	__device__ void updateHeat(float* updatedValue,float* ptrDevImageA,float k,int s,int w){
	float crtValue = ptrDevImageA[s];
	// cf. pdf page 2
	float north = ptrDevImageA[s-w];
	float south = ptrDevImageA[s+w];
	float west = ptrDevImageA[s-1];
	float east = ptrDevImageA[s+1];
	*updatedValue = crtValue+k*(north+south+east+west-4*crtValue);
	}

	/*--------------------------------------*\
	|*		Attributs		*|
	 \*-------------------------------------*/

    protected:

	// Input
	float k;

    };



#endif 



/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/

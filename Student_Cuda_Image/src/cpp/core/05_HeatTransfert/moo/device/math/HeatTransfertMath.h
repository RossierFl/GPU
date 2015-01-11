#ifndef HEAT_TRANSFERT_MATH_H_
#define HEAT_TRANSFERT_MATH_H_

#include "MathTools.h"

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

	__device__ HeatTransfertMath()
	    {

	    }

	__device__ HeatTransfertMath(const HeatTransfertMath& source)
	    {
	    // rien
	    }

	/*--------------------------------------*\
	|*		Methodes		*|
	 \*-------------------------------------*/

    public:




	__device__
	void calculeColorTransfert(float* centralColorOutput,float colorSud,float colorEst,float colorNord,float colorOuest,float k){
	   *centralColorOutput = *centralColorOutput + k*(colorSud+colorEst+colorNord+colorOuest);

	}

    private:



	/*--------------------------------------*\
	|*		Attributs		*|
	 \*-------------------------------------*/

    private:



    };

#endif 

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/

#ifndef HEAT_TRANSFERT_MATH_H_
#define HEAT_TRANSFERT_MATH_H_

#include "MathTools.h"
#include "ColorTools_GPU.h"
#include "CalibreurCudas.h"



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
	__device__
	void convertFloatToColor(float colorFloat , uchar4* color){
	    float hue = calibreur.calibrate(colorFloat);
	    ColorTools::HSB_TO_RVB(colorFloat,color);
	}

    private:



	/*--------------------------------------*\
	|*		Attributs		*|
	 \*-------------------------------------*/

    private:
	CalibreurCudas calibreur(0,1,0.7,0);



    };

#endif 

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/

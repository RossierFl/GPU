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

	__device__ HeatTransfertMath(int w, int h)
	    {
	    this->factor = 4 * PI / (float) w;
	    }

	__device__ HeatTransfertMath(const HeatTransfertMath& source)
	    {
	    // rien
	    }

	/*--------------------------------------*\
	|*		Methodes		*|
	 \*-------------------------------------*/

    public:

	/**
	 * x=pixelI
	 * y=pixelJ
	 */
	__device__
	void colorIJ(uchar4* ptrColor, int i, int j, float t)
	    {
	    unsigned char levelGris;

	    f(levelGris, i, j, t); // update levelGris

	    ptrColor->x = levelGris;
	    ptrColor->y = levelGris;
	    ptrColor->z = levelGris;

	    ptrColor->w = 255; // opaque
	    }

    private:

	__device__
	void f(unsigned char& levelGris, int i, int j, float t)
	    {
	    // Example1
	    //unsigned char levelGris= 255 * abs(sin(t)); // same color for all the image (Hello image)

	    // Example2
	    levelGris = 255 * fabs(sin(i * factor + t));
	    }

	/*--------------------------------------*\
	|*		Attributs		*|
	 \*-------------------------------------*/

    private:

	double factor;

    };

#endif 

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/

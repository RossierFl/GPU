#ifndef RIPPLING_0_MATH_H_
#define RIPPLING_0_MATH_H_

#include <math.h>
#include "MathTools.h"

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

class Rippling0Math
    {

	/*--------------------------------------*\
	|*		Constructor		*|
	 \*-------------------------------------*/

    public:

	__device__
	Rippling0Math(int w, int h)
	    {
	    // TODO
	    }

	__device__
	Rippling0Math(const Rippling0Math& source)
	    {
	    // TODO
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
	void color(int i, int j, float t, uchar4* ptrColor)
	    {
	    // Debug (a mettre en commentaire)
		{
		unsigned char levelGris = 128; //in [0.255]  (debug image)
		ptrColor->x = levelGris;
		ptrColor->y = levelGris;
		ptrColor->z = levelGris;
		}

	    // Vrai problem
		{
		// TODO
		}

	    //color.w = 255; // opaque
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

#ifndef VAGUE_0_MATH_
#define VAGUE_0_MATH_

#include "MathTools.h"

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

class Vague0Math
    {

	/*--------------------------------------*\
	|*		Constructor		*|
	 \*-------------------------------------*/

    public:

	__device__ Vague0Math(int w, int h)
	    {
	    this->factor = 4 * PI / (float) w;
	    }

	__device__ Vague0Math(const Vague0Math& source)
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

	    f(levelGris,i, j, t); // update levelGris

	    ptrColor->x = levelGris;
	    ptrColor->y = levelGris;
	    ptrColor->z = levelGris;

	    ptrColor->w = 255; // opaque
	    }

    private:

	__device__
	void f(unsigned char& levelGris,int i, int j, float t)
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

	float factor;

    };

#endif 

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/

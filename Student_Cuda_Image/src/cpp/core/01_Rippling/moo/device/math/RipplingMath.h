#ifndef RIPPLING_MATH_H_
#define RIPPLING_MATH_H_

#include <math.h>

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

class RipplingMath
    {

	/*--------------------------------------*\
	|*		Constructor		*|
	 \*-------------------------------------*/

    public:

	__device__
	RipplingMath(int w, int h)
	    {
	    // TODO
	    }

	__device__
	RipplingMath(const RipplingMath& source)
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
	void color(int i, int j, float t, uchar4& color)
	    {
	    // Debug (a mettre en commentaire)
		{
		unsigned char levelGris = 128; //in [0.255]  (debug image)
		color.x = levelGris;
		color.y = levelGris;
		color.z = levelGris;
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

	// Tools

    };

#endif 

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/

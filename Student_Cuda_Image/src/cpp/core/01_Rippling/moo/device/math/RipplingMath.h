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
	     this->dim2 = w / 2;
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
	void color( uchar4& color,int i, int j, float t)
	    {
	    // Debug (a mettre en commentaire)
		/*{
		unsigned char levelGris = 128; //in [0.255]  (debug image)
		color.x = levelGris;
		color.y = levelGris;
		color.z = levelGris;
		}*/

	    // Vrai problem
		{
		    float resulDXY = 0;
		    dxy(i,j, &resulDXY);
		    int levelGrey = 128 + 127 * cos(resulDXY/10.0-t/7.0) /(resulDXY/10.0+1.0);

		    color.x = levelGrey;
		    color.y = levelGrey;
		    color.z = levelGrey;
		    color.w = 255;
		}

	    //color.w = 255; // opaque
	    }

	__device__
	void dxy(int i, int j, float* ptrResult) // par exmple
		    {
		    //TODO
			double fx = i- dim2;
			double fy = j-dim2;
			*ptrResult = sqrt(fx*fx+fy*fy);
		    }

    private:

	/*--------------------------------------*\
	|*		Attributs		*|
	 \*-------------------------------------*/
	float dim2;

    private:

	// Tools

    };

#endif 

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/

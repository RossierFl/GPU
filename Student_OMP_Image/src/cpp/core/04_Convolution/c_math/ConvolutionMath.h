#ifndef CONVOLUTION_MATH_H_
#define CONVOLUTION_MATH_H_

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/
#include "cudaType.h"
#include <math.h>
/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

/**
 * Dans un header only pour preparer la version cuda
 */
class ConvolutionMath
    {

	/*--------------------------------------*\
	|*		Constructeur		*|
	 \*-------------------------------------*/

    public:

	ConvolutionMath(unsigned int w, unsigned int h)
	    {
	    this->dim2 = w / 2;
	    }

	virtual ~ConvolutionMath(void)
	    {
	    //rien
	    }

	/*--------------------------------------*\
	|*		Methode			*|
	 \*-------------------------------------*/

    public:

    	void colorIJ(uchar4* ptrColor, int i, int j, float t)
    	    {
    	    // TODO
    		float resulDXY = 0;
    		dxy(i,j, &resulDXY);
    		int levelGrey = 128 + 127 * cos(resulDXY/10.0-t/7.0) /(resulDXY/10.0+1.0);
    		ptrColor->x = levelGrey;
    		ptrColor->y = levelGrey;
    		ptrColor->z = levelGrey;
    		ptrColor->w = 255;
    	    }

    private:

	void dxy(int i, int j, float* ptrResult) // par exmple
	    {
	    //TODO
		double fx = i- dim2;
		double fy = j-dim2;
		*ptrResult = sqrt(fx*fx+fy*fy);
	    }



    private:

	/*--------------------------------------*\
	|*		Attribut		*|
	 \*-------------------------------------*/

    private:

	// Tools
	double dim2; //=dim/2

    };

#endif

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/

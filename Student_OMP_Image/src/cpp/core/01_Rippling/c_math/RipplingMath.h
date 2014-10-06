#ifndef RIPPLING_MATH_H_
#define RIPPLING_MATH_H_

#include "cudaType.h"
#include <math.h>

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

/**
 * Dans un header only pour preparer la version cuda
 */
class RipplingMath
    {

	/*--------------------------------------*\
	|*		Constructeur		*|
	 \*-------------------------------------*/

    public:

	RipplingMath(unsigned int w, unsigned int h)
	    {
	    this->dim2 = w / 2;
	    }

	    virtual ~RipplingMath(void)
		{
		//rien
		}

	    /*--------------------------------------*\
	|*		Methode			*|
	 \*-------------------------------------*/

public:

	    void colorIJ(uchar4* ptrColor, int i, int j, double t)
		{
	    float* ptrResult = new float[1];
	    dxy(i,j,ptrResult);
	    float result = *ptrResult;
	    double num = cos(result/10.0-(t/7.0));
	    float denom = result/10.0+1.0;
	    double finalResult = 128+127*num/denom;
	    ptrColor->x = finalResult;
	    ptrColor->y = finalResult;
	    ptrColor->z = finalResult;
	    ptrColor->w = 255;
		}

private:

	    void dxy(int i, int j, float* ptrResult) // par exmple
		{
	    ptrResult[0] = sqrt(pow(i-dim2,2)+pow(j-dim2,2));
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

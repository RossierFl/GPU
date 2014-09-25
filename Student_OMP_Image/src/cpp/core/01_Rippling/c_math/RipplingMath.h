#ifndef RIPPLING_MATH_H_
#define RIPPLING_MATH_H_

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

	void colorIJ(uchar4* ptrColor, int i, int j, float t)
	{
	    float dxyResult;
	    dxy(i, j, &dxyResult);

	    double sup = cos(0.1 * dxyResult - t / 7.); // (divisé par 10) devient (* 0.1)

	    float colorxy = 128 + 127 * sup / (dxyResult * 0.1 + 1);
	    ptrColor->x = colorxy;
	    ptrColor->y = colorxy;
	    ptrColor->z = colorxy;
	    ptrColor->w = 255;
	}

    private:

	void dxy(int i, int j, float* ptrResult) // par exmple
	{
	    float fx = i - dim2;
	    float fy = j - dim2;
	    *ptrResult = sqrt(fx * fx + fy * fy);
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

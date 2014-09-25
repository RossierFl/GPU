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
	      float dxy_val = 0.0;
	      dxy(i,j,&dxy_val);
	      double numerator = cos(dxy_val/10-t/7);
	      double denominator = dxy_val/10+1;
	      double result = 128+127*numerator/denominator;
	      ptrColor->x = result;
	      ptrColor->y = result;
	      ptrColor->z = result;
	      ptrColor->w = 255;
	    }

    private:

	void dxy(int i, int j, float* ptrResult) // par exmple
	    {
	      double fx = i-this->dim2;
	      double fy = j-this->dim2;

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

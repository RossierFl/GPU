#ifndef RIPPLING_MATH_H_
#define RIPPLING_MATH_H_
#include "math.h"
#include "cudaType.h"

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
	    float dxyres = 0.0f;
	    dxy(i,j,&dxyres);
	    float up = cosf(dxyres/10 - t/7);
	    float down = dxyres/10+1;
	    float levelGrey = 128 + 127 *(up/down);
	    ptrColor->x = levelGrey;
	    ptrColor->y = levelGrey;
	    ptrColor->z = levelGrey;
	    ptrColor->w = 255;
	    }

    private:

	void dxy(int i, int j, float* ptrResult) // par exmple
	    {
	    float fx = j - this->dim2;
	    float fy = i - this->dim2;
	    *ptrResult = sqrt(fx*fx + fy*fy);
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

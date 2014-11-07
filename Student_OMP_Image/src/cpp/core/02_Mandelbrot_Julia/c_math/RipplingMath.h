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

	FractalJuliaMath(unsigned int w, unsigned int h)
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

	void colorIJ(uchar4* ptrColor, int i, int j, int n)
	    {
		recusriveColorIJ(0,ptrColor,i,j,n, );
	    }

    private:
	int absZ(int x,int y)
	    {
	    return sqrt(x*x + y*y);
	    }
	bool isDivergent(int x, int y)
	    {
	    return absZ(x,y);
	    }
	void squareZ(int x, int yi, int* x2, int* yi2)
	    {
		*x2 = x*x - yi*yi;
		*yi2 = x*yi*2;
	    }
	void recusriveColorIJ(int k, uchar4* ptrColor, int i, int j, int n, int zx, int zyi)
	    {

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

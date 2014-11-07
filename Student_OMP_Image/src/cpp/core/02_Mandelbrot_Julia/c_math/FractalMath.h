#ifndef FRACTAL_MATH_H_
#define FRACTAL_MATH_H_
#include "math.h"
#include "cudaType.h"
#include "ColorTools.h"
#include "CalibreurF_CPU.h"
#define DIVERGENT_THRESHOLD 2.0

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

/**
 * Dans un header only pour preparer la version cuda
 */
class FractalMath
    {

	/*--------------------------------------*\
	|*		Constructeur		*|
	 \*-------------------------------------*/

    public:

	FractalMath(unsigned int w, unsigned int h)
	    {
	    this->dim2 = w / 2;
	    }

	virtual ~FractalMath(void)
	    {
	    //rien
	    }

	/*--------------------------------------*\
	|*		Methode			*|
	 \*-------------------------------------*/

    public:

	virtual void colorXY(uchar4* ptrColor, double x, double y, unsigned int n, double cx, double cyi,double x0, double y0)
	    {
		unsigned int k = 0;
		double zx = x0;
		double zyi = y0;
		while(k<=n && !isDivergent(zx,zyi))
		{
		    double xi = 0;
		    double yi = 0;
		    squareZ(zx,zyi,&xi,&yi);
		    //add to c
		    zx=xi+cx;zyi=yi+cyi;
		    k++;
		}
		if(k>n){
		    ptrColor->x=0;ptrColor->y=0;ptrColor->z=0;
		}else
		    ColorTools::HSB_TO_RVB(getHfromS(k, n), 1, 1, ptrColor);

		ptrColor->w=255;
	    }

    protected:
	double absZ(double x,double y)
	    {
	    return x*x + y*y;
	    }
	bool isDivergent(double x, double y)
	    {
	    return absZ(x,y) > DIVERGENT_THRESHOLD*DIVERGENT_THRESHOLD;
	    }
	void squareZ(double x, double yi, double* x2, double* yi2)
	    {
		*x2 = x*x - yi*yi;
		*yi2 = x*yi*2;
	    }
	double getHfromS(double k, unsigned int n)
	    {
	    return 1.0/n * k;
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

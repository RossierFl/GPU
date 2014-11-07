#ifndef FRACTAL_MATH_H_
#define FRACTAL_MATH_H_
#include <math.h>
#include "cudaType.h"
#include "ColorTools_GPU.h"
#include "CalibreurF_CPU.h"
#include <stdio.h>
#include "Indice2D.h"

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
	__device__
	FractalMath()
	    {
	    }
	__device__
	~FractalMath(void)
	    {
	    //rien
	    }

	/*--------------------------------------*\
	|*		Methode			*|
	 \*-------------------------------------*/



    protected:
	__device__
	bool isDivergent(float x, float y)
	    {
	    return (x*x + y*y) > 4.0;
	    }
	__device__
	void squareZ(float x, float yi, float* x2, float* yi2)
	    {
		*x2 = x*x - yi*yi;
		*yi2 = x*yi*2;
	    }
	__device__
	double getHfromS(float k, unsigned int n)
	    {
	    return 1.0/n * k;
	    }

    public:
    	__device__
    	void colorXY(uchar4* ptrColor, float x, float y, int n, float cx, float cyi,float x0, float y0)
    	    {
    		unsigned int k = 0;
    		float zx = x0;
    		float zyi = y0;
		while(k<=n && !isDivergent(zx,zyi))
		{
		    float xi = 0;
		    float yi = 0;
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

    private:
	/*--------------------------------------*\
	|*		Attribut		*|
	 \*-------------------------------------*/

    private:

    };

#endif

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/

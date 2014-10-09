#ifndef FRACTAL_H_
#define FRACTAL_H_

#include "ColorTools.h"
#include <math.h>
#include <iostream>
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

	/**
	 * calibreurColor : transformation affine entre [-1,1] (l'output de f(x,y)) et [0,1] (le spectre hsb)
	 */
  __device__ FractalMath(int n)
		//calibreur(IntervalF(-1, 1), IntervalF(0, 1))
	    {
	    this->n = n;
	    }

	__device__ ~FractalMath(void)
	    {
	    // rien
	    }

	__device__ virtual int indiceArret(double x, double y,int t)=0;

	/*--------------------------------------*\
	|*		Methode			*|
	 \*-------------------------------------*/

    public:

	__device__ void colorXY(uchar4* ptrColor, double x, double y, const DomaineMath& domaineMath, float t)
	    {

	    //int k =0;
	    int k = this->indiceArret(x,y,t);

	    if(k==n){
		//paint it black
		ptrColor->x = 0;
		ptrColor->y = 0;
		ptrColor->z = 0;
		//std::cout<<"black"<<std::endl;
	    }else{
		//HSB with h=h(k)
		double col = 1.0/t*(float)k;
		ColorTools::HSB_TO_RVB(col,ptrColor);

	    }
	    ptrColor->w = 255; // opaque

	    }

	/*--------------------------------------*\
	|*		Attribut		*|
	 \*-------------------------------------*/

    protected:

	// Inputs
	int n;

    }
;

#endif 

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/

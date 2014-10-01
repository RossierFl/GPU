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
class Fractal
    {
	/*--------------------------------------*\
	 |*		Constructeur		*|
	 \*-------------------------------------*/

    public:

	/**
	 * calibreurColor : transformation affine entre [-1,1] (l'output de f(x,y)) et [0,1] (le spectre hsb)
	 */
	Fractal(int n)
		//calibreur(IntervalF(-1, 1), IntervalF(0, 1))
	    {
	    this->n = n;
	    }

	virtual ~Fractal(void)
	    {
	    // rien
	    }

	virtual int indiceArret(double x, double y)=0;

	/*--------------------------------------*\
	|*		Methode			*|
	 \*-------------------------------------*/

    public:

	void colorXY(uchar4* ptrColor, double x, double y, const DomaineMath& domaineMath)
	    {

	    double k = this->indiceArret(x,y);

	    if(k==n){
		//paint it black
		ptrColor->x = 0;
		ptrColor->y = 0;
		ptrColor->z = 0;
		//std::cout<<"black"<<std::endl;
	    }else{
		//HSB with h=h(k)
		double col = 1.0/(float)n*k;
		ColorTools::HSB_TO_RVB(col,ptrColor);
		/*ptrColor->x = col;
		ptrColor->y = col;
		ptrColor->z = col;
		std::cout<<"computed"<<std::endl;*/

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

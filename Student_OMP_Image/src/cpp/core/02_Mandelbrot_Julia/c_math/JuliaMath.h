#ifndef JULIAMATH_H_
#define JULIAMATH_H_


#include "CalibreurF.h"
#include "ColorTools.h"
#include <math.h>
#include "Fractale.h"

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

/**
 * Dans un header only pour preparer la version cuda
 */
class JuliaMath : public Fractale
    {
	/*--------------------------------------*\
	 |*		Constructeur		*|
	 \*-------------------------------------*/

    public:

	/**
	 * calibreurColor : transformation affine entre [-1,1] (l'output de f(x,y)) et [0,1] (le spectre hsb)
	 */
	JuliaMath(int n, double c1, double c2) : Fractale(n)
	{
	this->c1 = c1;
	this->c2 = c2;
	}

	virtual ~JuliaMath(void)
	    {
	    // rien
	    }

	/*--------------------------------------*\
	|*		Methode			*|
	 \*-------------------------------------*/

    public:

	int indiceArret(double x, double y)
	    {
	int k = 0;
	double a = x;
	double b = y;
	while(((a*a)+(b*b))<4.0 && k < n )
	    {
	    double aCopy = a;
	    a = ((a*a)-(b*b))+c1;
	    b = (2.0*aCopy*b)+c2;
	    k++;
	    }
	return k;
	    }

    protected:
	double c1;
	double c2;

    }
;

#endif 

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/

#ifndef FRACTAL_MOO_H_
#define FRACTAL_MOO_H_

#include "cudaType.h"

#include "VariateurF.h"
#include "DomaineMath.h"
#include "Fractal.h"
#include "FractalMandelbrot.h"
#include "FractalJulia.h"


/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

class FractalMOO
    {
	/*--------------------------------------*\
	 |*		Constructeur		*|
	 \*-------------------------------------*/

    public:

	FractalMOO(unsigned int w, unsigned int h, int n, bool julia, double cx, double cy);
	virtual ~FractalMOO(void);

	/*--------------------------------------*\
	|*		Methode			*|
	 \*-------------------------------------*/

    public:

	void process(uchar4* ptrTabPixels, int w, int h, const DomaineMath& domaineMath);

	int getN();


    private:

	void forAutoOMP(uchar4* ptrTabPixels, int w, int h, const DomaineMath& domaineMath);
	void entrelacementOMP(uchar4* ptrTabPixels, int w, int h, const DomaineMath& domaineMath);

	void workPixel(uchar4* ptrColorIJ,int i, int j,int s, const DomaineMath& domaineMath,Fractal* ptrFractalMath);

	/*--------------------------------------*\
	|*		Attribut		*|
	 \*-------------------------------------*/

    protected:

	// Inputs
	int n;
	double cx;
	double cy;
	bool julia;
	unsigned int w;
	unsigned int h;

	// Tools
	bool isEntrelacement;
    };

#endif 

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/

#ifndef FRACTAL_MOO_H_
#define FRACTAL_MOO_H_

#include "cudaType.h"
#include "DomaineMath.h"
#include "FractalMath.h"
#include "VariateurI.h"

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

	FractalMOO(unsigned int w, unsigned int h, unsigned int nMin, unsigned int nMax, float cx, float cyi, bool isJulia);
	virtual ~FractalMOO(void);

	/*--------------------------------------*\
	|*		Methode			*|
	 \*-------------------------------------*/

    public:

	void process(uchar4* ptrTabPixels, int w, int h, const DomaineMath& domaineMath);
	void animationStep();
	float getT();

    private:

	void entrelacementOMP(uchar4* ptrTabPixels,int w,int h, const DomaineMath& domaineMath); 	// Code entrainement Cuda
	void forAutoOMP(uchar4* ptrTabPixels,int w, int h, const DomaineMath& domaineMath); 		// Code naturel et direct OMP, plus performsnt
	void workPixel(uchar4* ptrColorIJ,int i, int j, unsigned int n, const DomaineMath& domaineMath);

	/*--------------------------------------*\
	|*		Attribut		*|
	 \*-------------------------------------*/

    private:

	// Inputs
	double cx,cyi;
	bool isJulia;

	// Tools
	double t;
	bool isEntrelacement;
	FractalMath* ptrMath;
	VariateurI* variateur;
    };

#endif

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/

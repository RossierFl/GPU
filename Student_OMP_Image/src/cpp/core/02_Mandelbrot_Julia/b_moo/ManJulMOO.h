#ifndef MANJULMOO_H_
#define MANJULMOO_H_

#include "cudaType.h"

#include "VariateurF.h"
#include "DomaineMath.h"
#include "JuliaMath.h"
#include "MandelbrotMath.h"
#include "Fractale.h"


/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

class ManJulMOO
    {
	/*--------------------------------------*\
	 |*		Constructeur		*|
	 \*-------------------------------------*/

    public:

	ManJulMOO(unsigned int w, unsigned int h, float dt, int n, int isJulia, double c1, double c2);
	virtual ~ManJulMOO(void);

	/*--------------------------------------*\
	|*		Methode			*|
	 \*-------------------------------------*/

    public:

	void process(uchar4* ptrTabPixels, int w, int h, const DomaineMath& domaineMath);

	int getN();
	float getT();

	void animationStep();

    private:

	void forAutoOMP(uchar4* ptrTabPixels, int w, int h, const DomaineMath& domaineMath);
	void entrelacementOMP(uchar4* ptrTabPixels, int w, int h, const DomaineMath& domaineMath);

	void workPixel(uchar4* ptrColorIJ,int i, int j,int s, const DomaineMath& domaineMath,Fractale* ptrFractale);

	/*--------------------------------------*\
	|*		Attribut		*|
	 \*-------------------------------------*/

    protected:

	// Inputs
	int n;
	unsigned int w;
	unsigned int h;
	int isJulia;
	double c1;
	double c2;

	// Tools
	VariateurF variateurT; // fait varier para animation t
	bool isEntrelacement;
    };

#endif 

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/

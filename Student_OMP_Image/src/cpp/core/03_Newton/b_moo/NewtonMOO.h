#ifndef NEWTON_MOO_H_
#define NEWTON_MOO_H_

#include "cudaType.h"

#include "VariateurF.h"
#include "DomaineMath.h"
#include "NewtonMath.h"


/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

class NewtonMOO
    {
	/*--------------------------------------*\
	 |*		Constructeur		*|
	 \*-------------------------------------*/

    public:

	NewtonMOO(unsigned int w, unsigned int h, float dt, int n);
	virtual ~NewtonMOO(void);

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

	void workPixel(uchar4* ptrColorIJ,int i, int j,int s, const DomaineMath& domaineMath,NewtonMath* ptrNewtonMath);

	/*--------------------------------------*\
	|*		Attribut		*|
	 \*-------------------------------------*/

    protected:

	// Inputs
	int n;
	unsigned int w;
	unsigned int h;

	// Tools
	VariateurF variateurT; // fait varier para animation t
	bool isEntrelacement;
    };

#endif 

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/

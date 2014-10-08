#ifndef MandelbrotJulia_MOO_H_
#define MandelbrotJulia_MOO_H_

#include "cudaType.h"

#include "VariateurF.h"
#include "DomaineMath.h"
#include "MandelbrotJuliaMath.h"


/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

class MandelbrotJuliaMOO
    {
	/*--------------------------------------*\
	 |*		Constructeur		*|
	 \*-------------------------------------*/

    public:

	MandelbrotJuliaMOO(unsigned int w, unsigned int h, float dt, int n,bool isJulia,double cX,double cY);
	virtual ~MandelbrotJuliaMOO(void);

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

	void workPixel(uchar4* ptrColorIJ,int i, int j,int s, const DomaineMath& domaineMath,MandelbrotJuliaMath* ptrMandelbrotJuliaMath);

	/*--------------------------------------*\
	|*		Attribut		*|
	 \*-------------------------------------*/

    protected:

	// Inputs
	int n;
	unsigned int w;
	unsigned int h;
	double cX;
	double cY;
	bool isJulia;

	// Tools
	VariateurF variateurT; // fait varier para animation t
	bool isEntrelacement;
    };

#endif 

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/

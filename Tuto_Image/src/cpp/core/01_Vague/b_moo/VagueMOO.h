#ifndef VAGUE_MOO_H_
#define VAGUE_MOO_H_

#include "cudaType.h"


/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

class VagueMOO
    {

	/*--------------------------------------*\
	 |*		Constructeur		*|
	 \*-------------------------------------*/

    public:

	VagueMOO(unsigned int w, unsigned int h, float dt);
	virtual ~VagueMOO(void);

	/*--------------------------------------*\
	 |*		Methode			*|
	 \*-------------------------------------*/

    public:

	void  process(uchar4* ptrTabPixels, int w, int h);
	void animationStep();
	float getT();
	float getDT();

    private:

	// Balayage image
	void entrelacementOMP(uchar4* ptrTabPixels,int w, int h);
	void forAutoOMP(uchar4* ptrTabPixels,int w, int h);

	/*--------------------------------------*\
	|*		Attribut		*|
	 \*-------------------------------------*/

    private:

	// Inputs
	double dt;
	unsigned char w;

	// Tools
	double t;
	bool isEntrelacement;
    };

#endif

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 /*----------------------------------------------------------------------*/

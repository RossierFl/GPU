#ifndef RIPPLING_H_
#define RIPPLING_H_

#include "cudaTools.h"
#include "Animable_I.h"
#include "MathTools.h"

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

class MandelbrotJulia: public Animable_I
    {
	/*--------------------------------------*\
	|*		Constructor		*|
	 \*-------------------------------------*/

    public:

	MandelbrotJulia(int w, int h, float dt = 2 * PI / 10);
	virtual ~MandelbrotJulia(void);

	/*--------------------------------------*\
	 |*		Methodes		*|
	 \*-------------------------------------*/

    public:

	/*----------------*\
	|*  Override	  *|
	 \*---------------*/

	virtual void runGPU(uchar4* ptrDevPixels);
	virtual void animationStep(void);

	virtual float getT(void);
	virtual int getW(void);
	virtual int getH(void);

	virtual string getTitle(void);

    private:

	/*--------------------------------------*\
	 |*		Attributs		*|
	 \*-------------------------------------*/

    private:

	// Inputs
	int w;
	int h;
	float dt;

	// Tools
	dim3 dg;
	dim3 db;
	float t;

	//Outputs
	string title;
    };

#endif

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/

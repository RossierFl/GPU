#ifndef HEAT_TRANSFERT_H_
#define HEAT_TRANSFERT_H_

#include "cudaTools.h"
#include "Animable_I.h"
#include "MathTools.h"

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

class HeatTransfert: public Animable_I
    {
	/*--------------------------------------*\
	|*		Constructor		*|
	 \*-------------------------------------*/

    public:

	HeatTransfert(int w, int h, float dt = 2 * PI / 1000);
	virtual ~HeatTransfert(void);

	/*--------------------------------------*\
	 |*		Methodes		*|
	 \*-------------------------------------*/

    public:

	/*----------------*\
	|*  Override	  *|
	\*---------------*/

	/**
	 * Override
	 * Call periodicly by the API
	 */
	virtual void animationStep(void);

	virtual void runGPU(uchar4* ptrDevPixels); // Override

	virtual float getT(void); // Override
	virtual int getW(void); // Override
	virtual int getH(void); // Override

	virtual string getTitle(void); // Override

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

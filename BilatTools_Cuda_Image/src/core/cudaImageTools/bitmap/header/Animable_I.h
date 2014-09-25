#ifndef ANIMABLE_I_H_
#define ANIMABLE_I_H_

#include <iostream>
#include "cudaTools.h"

using std::string;

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

class Animable_I
    {
    public:

	//virtual ~Animable_I(void)=0;

	virtual void runGPU(uchar4* ptrDevPixels)=0;
	virtual void animationStep(void)=0;

	virtual int getW()=0;
	virtual int getH()=0;

	/**
	 * getParaAnimation
	 */
	virtual float getT()=0;

	virtual string getTitle()=0;

    };

#endif

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/


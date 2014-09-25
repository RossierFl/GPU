#ifndef ANIMABLE_FONCTIONEL_I_H_
#define ANIMABLE_FONCTIONEL_I_H_

#include <iostream>

#include "cudaTools.h"
#include "DomaineMath.h"

using std::string;



/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

class AnimableFonctionel_I
    {
    public:

	//virtual ~Animable_I(void)=0;

	virtual void runGPU(uchar4* ptrDevPixels,const DomaineMath& domaineMath)=0;
	virtual void animationStep(void)=0;

	virtual int getW(void)=0;
	virtual int getH(void)=0;
	virtual DomaineMath* getDomaineMathInit(void)=0;

	/**
	 * getParaAnimation
	 */
	virtual float getT(void)=0;

	virtual string getTitle(void)=0;

    };

#endif

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/


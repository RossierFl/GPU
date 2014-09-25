#ifndef EVENT_H_
#define EVENT_H_

#include "cudaTools.h"
#include "AnimableFonctionel_I.h"
#include "MathTools.h"

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

class Event: public AnimableFonctionel_I
    {
	/*--------------------------------------*\
	|*		Constructor		*|
	 \*-------------------------------------*/

    public:

	Event(int w,int h,float dt= 2*PI/1000);
	virtual ~Event(void);

	/*--------------------------------------*\
	 |*		Methodes		*|
	 \*-------------------------------------*/

    public:

	void runGPU(uchar4* ptrDevPixels,const DomaineMath& domaineMath); // Override
	void animationStep(void); // Overrideb

	float getT(void);// Override
	int getW(void);// Override
	int getH(void);// Override
	DomaineMath* getDomaineMathInit(void);// Override
	string getTitle(void);// Override


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
	DomaineMath* ptrDomaineMathInit;

	//Outputs
	string title;
    };

#endif

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/

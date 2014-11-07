#ifndef FRACTAL_H_
#define HELLO_FONCTIONEL_H_

#include "cudaTools.h"
#include "AnimableFonctionel_I.h"
#include "MathTools.h"
#include "VariateurF.h"

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

class Fractal: public AnimableFonctionel_I
    {
	/*--------------------------------------*\
	|*		Constructor		*|
	 \*-------------------------------------*/

    public:

	Fractal(unsigned int w, unsigned int h, unsigned int nMin, unsigned int nMax, double cx, double cyi, bool isJulia, double x0, double x1, double y0, double y1);
	virtual ~Fractal(void);

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

	void runGPU(uchar4* ptrDevPixels, const DomaineMath& domaineMath); // Override

	/**
	 * Para animation
	 */
	float getT(void); // Override
	int getW(void); // Override
	int getH(void); // Override
	DomaineMath* getDomaineMathInit(void); // Override
	string getTitle(void); // Override



	/*--------------------------------------*\
	 |*		Attributs		*|
	 \*-------------------------------------*/

    private:

	// Inputs
	int w;
	int h;
	int n;
	double cx,cyi;
	bool isJulia;
	double x0;
	double x1;
	double y0;
	double y1;

	// Tools
	dim3 dg;
	dim3 db;
	float t; // para animation
	VariateurF variateurAnimation; // varier t
	DomaineMath* ptrDomaineMathInit;

	//Outputs
	string title;
    };

#endif

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/

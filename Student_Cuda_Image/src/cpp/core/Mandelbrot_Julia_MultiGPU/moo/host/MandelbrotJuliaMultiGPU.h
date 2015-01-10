#ifndef MANDELBROT_JULIA_MULTIGPU_H_
#define HELLO_FONCTIONEL_MULTIGPU_H_

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

class MandelbrotJuliaMultiGPU: public AnimableFonctionel_I
    {
	/*--------------------------------------*\
	|*		Constructor		*|
	 \*-------------------------------------*/

    public:

	MandelbrotJuliaMultiGPU(int w, int h, float dt, int n,float xMin,float xMax,float yMin,float yMax,bool isJulia,float cX,float cY);
	virtual ~MandelbrotJuliaMultiGPU(void);

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
	float cX;
	float cY;
	bool isJulia;

	// Tools
	dim3 dg;
	dim3 db;
	float t; // para animation
	VariateurF variateurAnimation; // varier t
	DomaineMath* ptrDomaineMathInit;

	//Outputs
	string title;

	//Morceau MultiGPU


	//Share mutli GPU
	    uchar4* ptrDevPixels1;
	    uchar4* ptrDevPixels2;
	    uchar4* ptrDevPixels3;
	    uchar4* ptrDevPixels4;
	    uchar4* ptrDevPixels5;

    };

#endif

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/

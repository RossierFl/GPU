#ifndef FRACTAL_MULTI_H_
#define FRACTAL_MULTI_H_

#include "cudaTools.h"
#include "AnimableFonctionel_I.h"
#include "MathTools.h"
#include "VariateurI.h"

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

class FractalMulti: public AnimableFonctionel_I
    {
	/*--------------------------------------*\
	|*		Constructor		*|
	 \*-------------------------------------*/

    public:

	FractalMulti(int w, int h, int dt, int nMin,int nMax,bool julia,double cx,double cy,double xMin, double xMax, double yMin, double yMax);
	virtual ~FractalMulti(void);

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
	bool julia;
	double cx,cy;
	int nbGPU;
	int heightBande;
	size_t sizeBande;
	// Tools
	dim3 dg;
	dim3 db;
	float t; // para animation
	VariateurI variateurAnimation; // varier t
	DomaineMath* ptrDomaineMathInit;
	uchar4** bandeI;
	//std::vector<uchar4*> bandeI;
	//Outputs
	string title;
    };

#endif

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/

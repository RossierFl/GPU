#ifndef HEATTRANSFERT_H_
#define HEATTRANSFERT_H_

#include "cudaTools.h"
#include "Animable_I.h"
#include "MathTools.h"
#include "VariateurF.h"
#include "CalibreurCudas.h"

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

	HeatTransfert(int w, int h, float k);
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

	//void fillImageGL(uchar4* ptrDevImageGL, int w, int h);

	/**
	 * Para animation
	 */
	virtual float getT(void); // Override
	virtual int getW(void); // Override
	virtual int getH(void); // Override
	//DomaineMath* getDomaineMathInit(void); // Override
	virtual string getTitle(void); // Override



	/*--------------------------------------*\
	 |*		Attributs		*|
	 \*-------------------------------------*/

    private:

	// Inputs
	int w;
	int h;
	float k;

	// Tools
	dim3 dg;
	dim3 db;
	//float t; // para animation
	//VariateurF variateurAnimation; // varier t
	//DomaineMath* ptrDomaineMathInit;
	CalibreurCudas calibreurCuda;

	float* ptrDevImageInit;
	float* ptrDevImageHeater;
	float* ptrDevImageA;
	float* ptrDevImageB;

	//Outputs
	string title;
    };

#endif

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/

#ifndef CONVOLUTION_H_
#define CONVOLUTION_H_


/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

#include "cudaTools.h"
#include "Animable_I.h"
#include "MathTools.h"
#include "CaptureVideo.h"

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

class Convolution: public Animable_I
    {
	/*--------------------------------------*\
	|*		Constructor		*|
	 \*-------------------------------------*/

    public:

	Convolution();
	virtual ~Convolution(void);

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

	void fillDetourage(float* ptrNoyau);

	/*--------------------------------------*\
	 |*		Attributs		*|
	 \*-------------------------------------*/

    private:

	// Inputs
	int w;
	int h;
	float dt;
	int k;

	// Tools
	dim3 dg;
	dim3 db;
	float t;

	//Outputs
	string title;

	// noyau convolution
	float* ptrHostNoyau;
	float* ptrDeviceNoyau;

	// capture video
	string videoPath;
	string videoTitle;
	CaptureVideo* captureur;
	uchar4* ptrHostMemory;


	size_t sizeSM;
	uchar* ptrDevResult;
	uchar* ptrHostResult;
	size_t sizeResult;
    };

#endif 

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/

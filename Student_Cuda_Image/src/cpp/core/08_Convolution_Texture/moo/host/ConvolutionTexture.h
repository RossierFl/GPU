#ifndef CONVOLUTIONTEXTURE_H_
#define CONVOLUTIONTEXTURE_H_


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

class ConvolutionTexture: public Animable_I
    {
	/*--------------------------------------*\
	|*		Constructor		*|
	 \*-------------------------------------*/

    public:

	ConvolutionTexture();
	virtual ~ConvolutionTexture(void);

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
	size_t sizeConvSM;
	uchar* ptrDevResult;
	uchar* ptrHostResult;
	size_t sizeResult;

	size_t pitch; //taille en octets d'une ligne
	cudaChannelFormatDesc channelDesc;
    };

#endif 

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/

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

	HeatTransfert(int w, int h, float dt,float k);
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

	void initGPUMemory(int h, int w);

	void createDataForGPU(int h, int w);

	void initGPUFirstStep(int h, int w, float k);

	void freeGPUMemory();


	// Inputs
	int w;
	int h;
	float dt;
	float k;

	const int NB_ITERATION_AVEUGLE = 50;

	// Tools
	dim3 dg;
	dim3 db;
	float t;
	int iteration_aveugle_counter=0;
	//Outputs
	string title;

	//Images memory
	uchar4* ptrImageDeviceA;
	uchar4* ptrImageDeviceB;
	uchar4* prtImageHeats;

    };

#endif

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/

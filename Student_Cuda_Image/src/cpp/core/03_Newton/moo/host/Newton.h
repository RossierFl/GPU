#ifndef NEWTON_H_
#define NEWTON_H_

#include "cudaTools.h"
#include "AnimableFonctionel_I.h"
#include "MathTools.h"
#include "VariateurF.h"

/*----------------------------------------------------------------------*\
|*			Declaration 			                            		*|
\*-------------------------------------------------------------- -------*/

/*-------------------------------------*\
|*		Public			               *|
\*-------------------------------------*/

class Newton : public AnimableFonctionel_I
{

/*-------------------------------------*\
|*		Constructor		               *|
\*-------------------------------------*/

public:

	Newton(int w, int h, float dt, float epsilonx, float epsilonf, float epsilonxstar, double x1, double y1, double x2, double y2);

	virtual ~Newton();

/*-------------------------------------*\
|*		Methods		                   *|
\*-------------------------------------*/

public:

	/**
	* Update t
	* Call periodically by the API
	*/
	virtual void animationStep();

	/**
	* Run the computation on the GPU
	*/
	void runGPU(uchar4* ptrDevPixels, const DomaineMath& domaineMath);

	/**
	* Get the current animation parameter
	*/
	float getT();

	/**
	* Get the width of the fractal
	*/
	int getW();

	/**
	* Get the height of the fractal
	*/
	int getH();

	/**
	* Get the mathematical domain.
	*/
	DomaineMath* getDomaineMathInit();

	/**
	* Get the title of the fractal
	*/
	std::string getTitle();


/*-------------------------------------*\
|*		Attributs		               *|
\*-------------------------------------*/

private:

	// Inputs
	int w; // width
	int h; // height
	int n; // todo
	float epsilonx; // todo
	float epsilonf; // todo
	float epsilonxstar; // todo

	// Tools
	dim3 dg; // configuration of the grid
	dim3 db; // configuration of the blocks
	float t; // animation parameter
	bool tAdd;
	VariateurF animationVariator; // used to variate t
	DomaineMath* ptrDomaineMathInit;
};

#endif

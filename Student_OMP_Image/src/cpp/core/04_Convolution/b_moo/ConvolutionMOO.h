#ifndef CONVOLUTION_MOO_H_
#define CONVOLUTION_MOO_H_

#include "cudaType.h"

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

class ConvolutionMOO
    {

	/*--------------------------------------*\
	|*		Constructeur		*|
	 \*-------------------------------------*/

    public:

	ConvolutionMOO(unsigned int w, unsigned int h, float dt);
	virtual ~ConvolutionMOO(void);

	/*--------------------------------------*\
	|*		Methode			*|
	 \*-------------------------------------*/

    public:

	void process(uchar4* ptrTabPixels, int w, int h);
	void animationStep();
	float getT();

    private:

	void entrelacementOMP(uchar4* ptrTabPixels,int w,int h); 	// Code entrainement Cuda
	void forAutoOMP(uchar4* ptrTabPixels,int w, int h); 		// Code naturel et direct OMP, plus performsnt

	/*--------------------------------------*\
	|*		Attribut		*|
	 \*-------------------------------------*/

    private:

	// Inputs
	double dt;

	// Tools
	double t;
	bool isEntrelacement;



    };

#endif

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/

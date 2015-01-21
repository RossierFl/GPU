#include <iostream>
#include <omp.h>
#include "IndiceTools.h"
#include "OmpTools.h"

#include "ConvolutionMOO.h"
#include "ConvolutionMath.h"


using std::cout;
using std::endl;
using std::string;

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

/*--------------------------------------*\
 |*		Private		#include "cudaType.h"
#include "MathTools.h"	*|
 \*-------------------------------------*/

/*----------------------------------------------------------------------*\
 |*			Implementation 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

ConvolutionMOO::ConvolutionMOO(unsigned int w, unsigned int h, float dt)
    {
    this->t=0;
    this->dt=dt;
    }

ConvolutionMOO::~ConvolutionMOO(void)
    {
    // rien
    }


/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

void ConvolutionMOO::process(uchar4* ptrTabPixels, int w, int h)
    {
 /*   if (isEntrelacement)
	{
	entrelacementOMP(ptrTabPixels,w,h); // Plus lent
	}
    else
	{
	forAutoOMP(ptrTabPixels,w,h);  // Plus rapide
	}

    isEntrelacement=!isEntrelacement;// Pour tester que les deux implementations fonctionnent*/

    }


void ConvolutionMOO::animationStep()
    {
    t+=dt;
    }

/*--------------*\
 |*	get	*|
 \*-------------*/

float ConvolutionMOO::getT()
    {
    return t;
    }

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/






/*void ConvolutionMOO::entrelacementOMP(uchar4* ptrTabPixels,int w, int h)
    {
    ConvolutionMath convolutionMath(w,h);


     const int WH = w * h;


 #pragma omp parallel
 	{
 	const int NB_THREAD = OmpTools::getNbThread();// dans region parallel
 	const int TID = OmpTools::getTid();
 	int s = TID; // in [0,...

 	int i;
 	int j;
 	while (s < WH)
 	    {
 	    IndiceTools::toIJ(s, w, &i, &j); // s[0,W*H[ --> i[0,H[ j[0,W[

 	   convolutionMath.colorIJ(&ptrTabPixels[s], i, j,t);

 	    s += NB_THREAD;
 	    }
 	}
    }*/

/**
 * Code naturel et direct OMP
 */
/*void ConvolutionMOO::forAutoOMP(uchar4* ptrTabPixels,int w,int h)
    {
    // TODO
    ConvolutionMath convolutionMath(w,h); // ici pour preparer cuda
#pragma omp paralllel for
    for (int i=0;i<h ;i++){

	for (int j=0;j< w;j++){

	    int s = IndiceTools::toS(w, i, j);    // i[0,H[ j[0,W[  --> s[0,W*H[
	    convolutionMath.colorIJ(ptrTabPixels,  i,  j,  t);
	   // vagueMath.colorIJ(&ptrTabPixels[s], i, j,t);
	}
    }
    }
*/
/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/

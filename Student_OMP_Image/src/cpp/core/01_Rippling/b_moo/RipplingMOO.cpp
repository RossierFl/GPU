#include <iostream>
#include <omp.h>

#include "RipplingMOO.h"
#include "OmpTools.h"
#include "RipplingMath.h"
#include "IndiceTools.h"

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
 |*		Private			*|
 \*-------------------------------------*/

/*----------------------------------------------------------------------*\
 |*			Implementation 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

RipplingMOO::RipplingMOO(unsigned int w, unsigned int h, float dt)
    {
    //inputs
    this->dt=dt;

    //tools
    this->t=0;
    }

RipplingMOO::~RipplingMOO(void)
    {
    // rien
    }


/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

void RipplingMOO::process(uchar4* ptrTabPixels, int w, int h)
    {
    if (isEntrelacement)
	{
	entrelacementOMP(ptrTabPixels,w,h); // Plus lent
	}
    else
	{
	forAutoOMP(ptrTabPixels,w,h);  // Plus rapide
	}

    isEntrelacement=!isEntrelacement;// Pour tester que les deux implementations fonctionnent
    }


void RipplingMOO::animationStep()
    {
    t+=dt;
    }

/*--------------*\
 |*	get	*|
 \*-------------*/

float RipplingMOO::getT()
    {
    return t;
    }

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

/**
 * Code entrainement Cuda
 */
void RipplingMOO::entrelacementOMP(uchar4* ptrTabPixels, int w, int h)
    {
    RipplingMath ripplingMath(w,h);

    const int NB_THREADS = OmpTools::setAndGetNaturalGranularity();
    const int SIZE = w*h;
#pragma omp parallel
    {
    const int TID = OmpTools::getTid();
    int s = TID;
    int i =0;
    int j =0;
    while(s<SIZE){
	IndiceTools::toIJ(s, w, &i, &j); // s[0,W*H[ --> i[0,H[ j[0,W[
	ripplingMath.colorIJ(&ptrTabPixels[s], i, j,t);
	s+=NB_THREADS;
    }
    }
    }

/**
 * Code naturel et direct OMP
 */
void RipplingMOO::forAutoOMP(uchar4* ptrTabPixels,int w, int h)
    {
    RipplingMath ripplingMath(w,h);
#pragma omp parallel for
        for(int i = 0;i<h;i++)
            {
            for(int j = 0;j<w;j++)
        	{
        	int s = IndiceTools::toS(w, i, j);
        	ripplingMath.colorIJ(&ptrTabPixels[s], i, j,t);
        	}
            }
    }

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/

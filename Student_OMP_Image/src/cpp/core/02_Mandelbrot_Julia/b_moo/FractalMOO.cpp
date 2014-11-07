#include <iostream>
#include <omp.h>

#include "FractalMOO.h"
#include "OmpTools.h"
#include "FractalMath.h"
#include "IndiceTools.h"
#include "DomaineMath.h"
#include "VariateurI.h"

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

FractalMOO::FractalMOO(unsigned int w, unsigned int h, unsigned int nMin, unsigned int nMax, float cx, float cyi, bool isJulia)
    {
    //inputs
    this->cx = cx;
    this->cyi = cyi;
    this->isEntrelacement = false;
    this->ptrMath = ptrMath;
    this->isJulia = isJulia;
    //tools
    this->t=0;
    this->ptrMath = new FractalMath(w,h);
    IntervalI interval(nMin,nMax);
    this->variateur = new VariateurI(interval,1);
    }

FractalMOO::~FractalMOO(void)
    {
    // rien
    }


/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

void FractalMOO::process(uchar4* ptrTabPixels, int w, int h, const DomaineMath& domaineMath)
    {
    if (isEntrelacement)
	{
	entrelacementOMP(ptrTabPixels,w,h, domaineMath); // Plus lent
	}
    else
	{
	forAutoOMP(ptrTabPixels,w,h, domaineMath);  // Plus rapide
	}

    isEntrelacement=!isEntrelacement;// Pour tester que les deux implementations fonctionnent
    }


void FractalMOO::animationStep()
    {
    variateur->varierAndGet();
    }

/*--------------*\
 |*	get	*|
 \*-------------*/

float FractalMOO::getT()
    {
    return variateur->get();
    }

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

/**
 * Code entrainement Cuda
 */
void FractalMOO::entrelacementOMP(uchar4* ptrTabPixels, int w, int h, const DomaineMath& domaineMath)
    {
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
	workPixel(&ptrTabPixels[s], i, j,getT(), domaineMath);
	s+=NB_THREADS;
    }
    }
    }

/**
 * Code naturel et direct OMP
 */
void FractalMOO::forAutoOMP(uchar4* ptrTabPixels,int w, int h, const DomaineMath& domaineMath)
    {
#pragma omp parallel for
        for(int i = 0;i<h;i++)
            {
            for(int j = 0;j<w;j++)
        	{
        	int s = IndiceTools::toS(w, i, j);
        	workPixel(&ptrTabPixels[s], i, j,getT(), domaineMath);
        	}
            }
    }

/**
 * i in [1,h]
 * j in [1,w]
 * code commun �
 * 	entrelacementOMP
 * 	forAutoOMP
 */
void FractalMOO::workPixel(uchar4* ptrColorIJ,int i, int j, unsigned int n, const DomaineMath& domaineMath)
    {
    // (i,j) domaine ecran dans N2
    // (x,y) domaine math dans R2

    double x = 0.0;
    double y = 0.0;

    domaineMath.toXY(i, j, &x, &y); // fill (x,y) from (i,j)

    if(isJulia)
	ptrMath->colorXY(ptrColorIJ,x, y, n, this->cx, this->cyi, x, y); // in [01]
    else
	ptrMath->colorXY(ptrColorIJ,x, y, n, x,y, 0,0);
    }

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/

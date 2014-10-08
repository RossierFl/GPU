#include <iostream>
#include <math.h>

#include "MandelbrotJuliaMOO.h"

#include "OmpTools.h"
#include "MathTools.h"

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

/**
 * variateurT: 	fait varier t in [0,2pi] par increment de dt,
 * 		d'abord de mani�re croissante jusqua 2PI, puis de maniere decroissante jusqua 0, puis en boucle a l'infini selon ce procede
 */
MandelbrotJuliaMOO::MandelbrotJuliaMOO(unsigned int w, unsigned int h, float dt, int n,bool isJulia,double cX=0,double cY=0):variateurT(IntervalF(20, 200),dt)
    {
    // Inputs
    this->n =n;
    this->w=w;
    this->h=h;
    this->cX=cX;
    this->cY=cY;
    this->isJulia=isJulia;

    //Tools
    this->isEntrelacement=false;

    // OMP (facultatif)
    const int NB_THREADS = OmpTools::setAndGetNaturalGranularity();
    cout << "\n[MandelbrotJulia] nbThread = " << NB_THREADS << endl;;
    }

MandelbrotJuliaMOO::~MandelbrotJuliaMOO(void)
    {
    // rien
    }

/*--------------------------------------*\
 |*		Override		*|
 \*-------------------------------------*/

void MandelbrotJuliaMOO::process(uchar4* ptrTabPixels, int w, int h, const DomaineMath& domaineMath)
    {
    if (isEntrelacement)
	{
	entrelacementOMP(ptrTabPixels,w,h,domaineMath); // Plus lent
	}
    else
	{
	forAutoOMP(ptrTabPixels,w,h,domaineMath);  // Plus rapide
	}

    isEntrelacement=!isEntrelacement; // Pour tester que les deux implementations fonctionnent
    }

void MandelbrotJuliaMOO::animationStep()
    {
    variateurT.varierAndGet();
    }

/*--------------*\
 |*	get	*|
 \*-------------*/

int MandelbrotJuliaMOO::getN()
    {
    return n;
    }

float MandelbrotJuliaMOO::getT()
    {
    return variateurT.get();
    }

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/


/**
 * Code naturel et direct OMP
 */
void MandelbrotJuliaMOO::forAutoOMP(uchar4* ptrTabPixels, int w, int h, const DomaineMath& domaineMath)
    {
    MandelbrotJuliaMath MandelbrotJuliaMath(n,isJulia,cX,cY); // ici pour preparer cuda

#pragma omp parallel for
    for (int i = 0; i < h; i++)
	{
	for (int j = 0; j < w; j++)
	    {
	    //int s = i * W + j;
	    int s=IndiceTools::toS(w,i,j);// i[0,H[ j[0,W[  --> s[0,W*H[

	    workPixel(&ptrTabPixels[s],i, j,s, domaineMath,&MandelbrotJuliaMath);
	    }
	}
    }

/**
 * Code entrainement Cuda
 */
void MandelbrotJuliaMOO::entrelacementOMP(uchar4* ptrTabPixels, int w, int h, const DomaineMath& domaineMath)
    {
    MandelbrotJuliaMath MandelbrotJuliaMath(n,isJulia,cX,cY);
    const int WH=w*h;



#pragma omp parallel
	{
	const int NB_THREAD = OmpTools::getNbThread(); // dans region parallel

	const int TID = OmpTools::getTid();
	int s = TID; // in [0,...

	int i;
	int j;
	while (s < WH)
	    {
	    IndiceTools::toIJ(s,w,&i,&j); // s[0,W*H[ --> i[0,H[ j[0,W[

	    workPixel(&ptrTabPixels[s],i, j,s, domaineMath,&MandelbrotJuliaMath);

	    s += NB_THREAD;
	    }
	}
    }

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

/**
 * i in [1,h]
 * j in [1,w]
 * code commun �
 * 	entrelacementOMP
 * 	forAutoOMP
 */
void MandelbrotJuliaMOO::workPixel(uchar4* ptrColorIJ,int i, int j,int s, const DomaineMath& domaineMath,MandelbrotJuliaMath* ptrMandelbrotJuliaMath)
    {
    MandelbrotJuliaMath MandelbrotJuliaMath(n,isJulia,cX,cY); // ici pour preparer cuda

    // (i,j) domaine ecran dans N2
    // (x,y) domaine math dans R2

    double x;
    double y;

    domaineMath.toXY(i, j, &x, &y); // fill (x,y) from (i,j)

    float t=variateurT.get();
   // float t=12;
    ptrMandelbrotJuliaMath->colorXY(ptrColorIJ,x, y, domaineMath,t); // in [01]
    }

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/


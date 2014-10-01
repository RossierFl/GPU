#include <iostream>
#include <math.h>

#include "FractalMOO.h"

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
FractalMOO::FractalMOO(unsigned int w, unsigned int h, int n, bool julia, double cx, double cy)
    {
    // Inputs
    this->n =n;
    this->w=w;
    this->h=h;
    this->cx = cx;
    this->cy = cy;
    this->julia = julia;

    //Tools
    this->isEntrelacement=true;

    // OMP (facultatif)
    const int NB_THREADS = OmpTools::setAndGetNaturalGranularity();
    cout << "\n[FRACTAL] nbThread = " << NB_THREADS << endl;;
    }

FractalMOO::~FractalMOO(void)
    {
    // rien
    }

/*--------------------------------------*\
 |*		Override		*|
 \*-------------------------------------*/

void FractalMOO::process(uchar4* ptrTabPixels, int w, int h, const DomaineMath& domaineMath)
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



/*--------------*\
 |*	get	*|
 \*-------------*/

int FractalMOO::getN()
    {
    return n;
    }



/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/


/**
 * Code naturel et direct OMP
 */
void FractalMOO::forAutoOMP(uchar4* ptrTabPixels, int w, int h, const DomaineMath& domaineMath)
    {
      Fractal* fractalMath;
      if(this->julia){
  	fractalMath = new FractalJulia(n,cx,cy);// ici pour preparer cuda
      }else{
  	fractalMath = new FractalMandelbrot(n);// ici pour preparer cuda
      }

#pragma omp parallel for
    for (int i = 0; i < h; i++)
	{
	for (int j = 0; j < w; j++)
	    {
	    //int s = i * W + j;
	    int s=IndiceTools::toS(w,i,j);// i[0,H[ j[0,W[  --> s[0,W*H[

	    workPixel(&ptrTabPixels[s],i, j,s, domaineMath, fractalMath);
	    }
	}
    }

/**
 * Code entrainement Cuda
 */
void FractalMOO::entrelacementOMP(uchar4* ptrTabPixels, int w, int h, const DomaineMath& domaineMath)
    {
    Fractal* fractalMath;
    if(this->julia){
	fractalMath = new FractalJulia(n,cx,cy);// ici pour preparer cuda
    }else{
	fractalMath = new FractalMandelbrot(n);// ici pour preparer cuda
    }

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

	    workPixel(&ptrTabPixels[s],i, j,s, domaineMath,fractalMath);

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
void FractalMOO::workPixel(uchar4* ptrColorIJ,int i, int j,int s, const DomaineMath& domaineMath,Fractal* ptrFractalMath)
    {

    // (i,j) domaine ecran dans N2
    // (x,y) domaine math dans R2
   // std::cout<<"print"<<std::endl;
    double x;
    double y;

    domaineMath.toXY(i, j, &x, &y); // fill (x,y) from (i,j)

    ptrFractalMath->colorXY(ptrColorIJ,x, y, domaineMath); // in [01]
    }

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/


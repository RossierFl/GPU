#include <omp.h>
#include "00_pi_tools.h"
#include "OmpTools.h"

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Imported	 	*|
 \*-------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

bool isPiOMPEntrelacerPromotionTab_Ok(int n);

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

static double piOMPEntrelacerPromotionTab(int n);

/*----------------------------------------------------------------------*\
 |*			Implementation 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

bool isPiOMPEntrelacerPromotionTab_Ok(int n)
    {
    return isAlgoPI_OK(piOMPEntrelacerPromotionTab, n, "Pi OMP Entrelacer promotionTab");
    }

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

/**
 * pattern cuda : excellent!
 */
double piOMPEntrelacerPromotionTab(int n)
    {

    const int NBTHREAD = OmpTools::setAndGetNaturalGranularity();

    double* tabSumThread = new double[NBTHREAD];
    const double DX = 1 / (double) n;

#pragma omp parallel
	{

	double xs;
	const int TID = OmpTools::getTid();
	int s = TID;

	while (s < n)
	    {
	    xs = s * DX;
	    tabSumThread[TID] += fpi(xs);

	    s += NBTHREAD;
	    }
	}

    // reduction sequentiel
    double sum = 0;
    for (int i = 0; i < NBTHREAD; i++)
	{
	sum += tabSumThread[i];
	}

    delete[] tabSumThread;

    return sum * DX;
    }

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/


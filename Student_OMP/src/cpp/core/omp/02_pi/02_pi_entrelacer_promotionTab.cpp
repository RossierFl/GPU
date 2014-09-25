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
    double sum = 0;
    double* tab  = new double[NBTHREAD];

    const double DX = 1.0 / (double) n;

#pragma omp parallel
	{
	const int ID = OmpTools::getTid();
        tab[ID] =0.0;
	double xs = 0;

	int s = ID;
	while (s < n)
	    {
	    xs = s * DX;
	    tab[ID] += fpi(xs);
	    s += NBTHREAD;
	    }
	}



    //reduction sequentiel
    for(int i=0;i<NBTHREAD;i++)sum+=tab[i];
    delete[] tab;
    return sum * DX;
    }

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/


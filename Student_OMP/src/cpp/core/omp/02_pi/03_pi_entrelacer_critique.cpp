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

bool isPiOMPEntrelacerCritical_Ok(int n);

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

static double piOMPEntrelacerCritical(int n);

/*----------------------------------------------------------------------*\
 |*			Implementation 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

bool isPiOMPEntrelacerCritical_Ok(int n)
    {
    return isAlgoPI_OK(piOMPEntrelacerCritical, n, "Pi OMP Entrelacer critical");
    }

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

double piOMPEntrelacerCritical(int n)
    {
    const int NB_THREAD = OmpTools::setAndGetNaturalGranularity();
    double finalSum = 0.0;
    const double DX = 1.0/(double)n;
#pragma omp parallel
    {
	double xs = 0.0;
	const int TID = OmpTools::getTid();
	double sumLocalThread = 0.0;
	int s = TID;
	while(s<n)
	    {
	    xs = s*DX;
	    sumLocalThread += fpi(xs);
	    s+=NB_THREAD;
	    }
#pragma omp critical(cs)
	{
	finalSum += sumLocalThread;
	}
    }
    return DX*finalSum;
    }

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/


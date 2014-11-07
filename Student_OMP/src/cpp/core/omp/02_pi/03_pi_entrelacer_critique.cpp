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
    const int NBTHREADS = OmpTools::setAndGetNaturalGranularity();
    double sum = 0;
    const double DX = 1 / (double) n;
#pragma omp parallel
	{
	int tid = OmpTools::getTid();
	double sumLocalThread = 0.0;
	int s = tid;
	double xs;
	while (s < n)
	    {
	    xs = s * DX;
	    sumLocalThread += fpi(xs);
	    s += NBTHREADS;
	    }
#pragma omp critical(section)
	    {
	    sum += sumLocalThread;
	    }
	}

    return sum * DX;
    }

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/


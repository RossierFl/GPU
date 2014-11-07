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
    return isAlgoPI_OK(piOMPEntrelacerPromotionTab,  n, "Pi OMP Entrelacer promotionTab");
    }

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

/**
 * pattern cuda : excellent!
 */
double piOMPEntrelacerPromotionTab(int n)
    {
    const int NBTHREADS = OmpTools::setAndGetNaturalGranularity();
    double sum = 0;
    const double DX = 1/(double)n;
    double* promotionTab = new double[NBTHREADS];
    #pragma omp parallel
    {
    int tid = OmpTools::getTid();
    promotionTab[tid]=0.0;
    int s = tid;
    double xs;
    while(s<n)
	{
	xs = s*DX;
	promotionTab[tid]+=fpi(xs);
	s+=NBTHREADS;
	}
    }
    for(int i = 0;i<NBTHREADS;i++)
	sum+=promotionTab[i];

    return sum*DX;
    }

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/


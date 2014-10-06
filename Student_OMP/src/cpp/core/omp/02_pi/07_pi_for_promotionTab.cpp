#include <string.h>
#include <omp.h>
#include "00_pi_tools.h"
#include "MathTools.h"
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

bool isPiOMPforPromotionTab_Ok(int n);

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

static double piOMPforPromotionTab(int n);
static void syntaxeSimplifier(double* tabSumThread,int n);
static void syntaxeFull(double* tabSumThread,int n);

/*----------------------------------------------------------------------*\
 |*			Implementation 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

bool isPiOMPforPromotionTab_Ok(int n)
    {
    return isAlgoPI_OK(piOMPforPromotionTab, n, "Pi OMP for promotion tab");
    }

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

/**
 * De-synchronisation avec PromotionTab
 */
double piOMPforPromotionTab(int n)
    {
        double xi = 0.0;
        const double DX = 1.0/(double)n;
        const int NB_THREAD = OmpTools::setAndGetNaturalGranularity();
        double* sum = new double[NB_THREAD];
        memset(sum, 0, NB_THREAD*sizeof(*sum));
        double finalSum = 0.0;
    #pragma omp parallel for private(xi)
        for(int i = 0;i<n;i++)
    	{
            const int TID = OmpTools::getTid();
    	xi = i*DX;
    	sum[TID] += fpi(xi);
    	}
        for(int i = 0;i<NB_THREAD;i++)
            {
		finalSum += sum[i];
            }
        delete[] sum;
        return DX * finalSum;
    }



/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/


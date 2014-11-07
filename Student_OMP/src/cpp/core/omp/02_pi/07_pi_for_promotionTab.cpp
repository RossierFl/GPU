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
    double sum = 0.0;
        double xi;
        const double DX = 1 / (double) n;
        const int NB_THREADS = OmpTools::setAndGetNaturalGranularity();//get threads number
        double tabSumThreads[NB_THREADS];
        for(int i = 0;i<n;i++)//init array
            tabSumThreads[i]=0.0;
    #pragma omp parallel for private(xi) //1 instance -> xi
        for (int i = 0; i < n; i++)
        {
	const int TID = OmpTools::getTid();//get id
        xi = i * DX;
        tabSumThreads[TID] += fpi(xi);
        }
        for(int i = 0;i<NB_THREADS;i++)//reduction
            sum+=tabSumThreads[i];
        return sum * DX;
    }



/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/


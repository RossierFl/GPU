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
    double somme=0;
        double xi;
        const double DX = 1.0/(double)n;
        int nbrThreads = OmpTools::setAndGetNaturalGranularity();
        double tabThreads [nbrThreads] ;
        for(int i=0;i<nbrThreads;i++)
            tabThreads[i]=0;
   #pragma omp parallel for private(xi)
        for(int i=1;i<n;i++){
    	xi= i*DX;
    	const int TID =   OmpTools::getTid();
   #pragma omp atomic
    	tabThreads[TID]+=fpi(xi);
        }
        for(int i=0;i<nbrThreads;i++)
            somme+=tabThreads[i];
        return somme*DX;
    }



/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/


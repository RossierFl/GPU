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

bool
isPiOMPforPromotionTab_Ok (int n);

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

static double
piOMPforPromotionTab (int n);
static void
syntaxeSimplifier (double* tabSumThread, int n);
static void
syntaxeFull (double* tabSumThread, int n);

/*----------------------------------------------------------------------*\
 |*			Implementation 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

bool
isPiOMPforPromotionTab_Ok (int n)
{
  return isAlgoPI_OK (piOMPforPromotionTab, n, "Pi OMP for promotion tab");
}

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

/**
 * De-synchronisation avec PromotionTab
 */
double
piOMPforPromotionTab (int n)
{
  double sum = 0;
  double xi = 0;
  const double DX = 1.0 / (double) n;
  const int NBTHREAD = OmpTools::setAndGetNaturalGranularity ();
  double tabSumThread[NBTHREAD];
  for(int i=0;i < NBTHREAD;i++)tabSumThread[i]=0.0;
#pragma omp parralel for private(xi) //xi one instance per thread
  for (int i = 1; i < n; i++)
    {
      const int tid = OmpTools::getTid ();
      xi = i * DX;
      tabSumThread[tid] += fpi (xi);
    }

  for(int i=0;i < NBTHREAD;i++)sum+=tabSumThread[i];
  //delete[] tabSumThread;
  return sum * DX;
}

    /*----------------------------------------------------------------------*\
 |*			End	 					*|
     \*---------------------------------------------------------------------*/


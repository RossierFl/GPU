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

void HistoOMPforPromotionTab(int* ptrData, int n, int* ptrResult, int histoSize);

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

/*static double
piOMPforPromotionTab (int n);
static void
syntaxeSimplifier (double* tabSumThread, int n);
static void
syntaxeFull (double* tabSumThread, int n);*/

/*----------------------------------------------------------------------*\
 |*			Implementation 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

/*bool
isPiOMPforPromotionTab_Ok (int n)
{
  return isAlgoPI_OK (piOMPforPromotionTab, n, "Pi OMP for promotion tab");
}*/

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

/**
 * De-synchronisation avec PromotionTab
 */
void HistoOMPforPromotionTab(int* ptrData, int n, int* ptrResult, int histoSize)
{
  const int NBTHREAD = OmpTools::setAndGetNaturalGranularity();
      int** tab  = new int*[NBTHREAD];
      for(int i = 0; i < NBTHREAD; ++i)
          tab[i] = new int[histoSize];
      printf("NBTHREAD : %d\n",NBTHREAD);

      for(int i=0;i<NBTHREAD;i++){
      	for(int j=0;j<histoSize;j++)
      	  {
      	    tab[i][j] = 0;
      	  }
          }
  #pragma omp parallel for
  	for (int i = 0; i < n; i++)
  	    {
  	      const int tid = OmpTools::getTid ();
  	      tab[tid][ptrData[i]]++;
  	    }
      //reduction sequentiel
      for(int i=0;i<NBTHREAD;i++){
  	for(int j=0;j<histoSize;j++)
  	  {
  	    ptrResult[j] += tab[i][j];
  	  }
      }

      //clean

      for(int i = 0; i < NBTHREAD; ++i)
  	delete[] tab[i];
      delete[] tab ;
  /*double sum = 0;
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
  return sum * DX;*/
}

    /*----------------------------------------------------------------------*\
 |*			End	 					*|
     \*---------------------------------------------------------------------*/


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

void HistoOMPforCritical(int* ptrData, int n, int* ptrResult, int histoSize);

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

/*static double
piOMPforCritique (int n);*/

/*----------------------------------------------------------------------*\
 |*			Implementation 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

/*bool
isPiOMPforCritical_Ok (int n)
{
  return isAlgoPI_OK (piOMPforCritique, n, "Pi OMP for critique");
}*/

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

/**
 * synchronisation couteuse!
 */
void HistoOMPforCritical(int* ptrData, int n, int* ptrResult, int histoSize)
{
#pragma omp parralel for

  for (int i = 0; i < n; i++)
    {

#pragma omp critical
	{
	  ptrResult[ptrData[i]]+=1;
	}
    }
}

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/


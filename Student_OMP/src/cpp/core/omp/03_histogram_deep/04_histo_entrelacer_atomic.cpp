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

void HistoOMPEntrelacerAtomic(int* ptrData, int n, int* ptrResult, int histoSize);

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

/*static double
piOMPEntrelacerAtomic (int n);*/

/*----------------------------------------------------------------------*\
 |*			Implementation 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

/*bool
isPiOMPEntrelacerAtomic_Ok (int n)
{
  return isAlgoPI_OK (piOMPEntrelacerAtomic, n, "Pi OMP Entrelacer atomic");
}*/

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

/**
 * Bonne performance, si!
 */
void HistoOMPEntrelacerAtomic(int* ptrData, int n, int* ptrResult, int histoSize)
{
  const int NBTHREAD = OmpTools::setAndGetNaturalGranularity ();

#pragma omp parallel
    {
      const int ID = OmpTools::getTid ();
      int s = ID;
      while (s < n)
	{
#pragma omp atomic
	  ptrResult[ptrData[s]] += 1;

	  s += NBTHREAD;
	}

    }

}

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/


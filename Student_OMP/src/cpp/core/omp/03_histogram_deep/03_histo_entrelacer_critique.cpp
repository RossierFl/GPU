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

void HistoOMPEntrelacerCritical(int* ptrData, int n, int* ptrResult, int histoSize);

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/


/*----------------------------------------------------------------------*\
 |*			Implementation 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

void HistoOMPEntrelacerCritical(int* ptrData, int n, int* ptrResult, int histoSize)
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
  #pragma omp parallel
  	{
  	const int ID = OmpTools::getTid();

  	int s = ID;
  	while (s < n)
  	    {
  	    tab[ID][ptrData[s]]++;
  	    s += NBTHREAD;
  	    }
#pragma omp critical
	  {
	  for(int j=0;j<histoSize;j++)
	    {
	      ptrResult[j] += tab[ID][j];
	    }
	  }
  	}
    //clean
      for(int i = 0; i < NBTHREAD; ++i)
	delete[] tab[i];
      delete[] tab ;
}

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/


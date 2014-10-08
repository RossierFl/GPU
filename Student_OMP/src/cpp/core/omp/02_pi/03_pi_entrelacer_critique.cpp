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
    const int NBTHREAD = OmpTools::setAndGetNaturalGranularity();
      double sum=0;
    //  double* tabSumThread = new double[NBTHREAD];
      const double DX = 1.0/(double)n;

      #pragma omp parallel
      {
  	double xs;
          int s = OmpTools::getTid();
          const int TID = OmpTools::getTid();
          double sumLocalThread =0;
          while(s<n){
              xs = s*DX;

              sumLocalThread+=fpi(xs);
             s+=NBTHREAD;
          }
#pragma omp critical(section)
          sum+=sumLocalThread;

      }

      return sum*DX;
    }

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/


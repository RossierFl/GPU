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

bool isPiOMPforReduction_Ok(int n);

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

static double piOMPforReduction(int n);

/*----------------------------------------------------------------------*\
 |*			Implementation 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

bool isPiOMPforReduction_Ok(int n)
    {
    return isAlgoPI_OK(piOMPforReduction, n, "Pi OMP for reduction-integrer");
    }

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

/**
 * pattern omp usefull : idem desyncronisation-promotionTab ,mais avec syntaxe plus courte!
 * Si on enleve le pragma, le code est le meme que le sequentiel!
 */
double piOMPforReduction(int n)
    {
      double sum = 0;
      double xi = 0;
      const double DX = 1.0/(double)n;
#pragma omp parralel for private(xi) reduction(+:sum)
      for(int i=1;i<n;i++){
  	xi = i*DX;
  	sum += fpi(xi);
      }
      return sum*DX;
    }




/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/


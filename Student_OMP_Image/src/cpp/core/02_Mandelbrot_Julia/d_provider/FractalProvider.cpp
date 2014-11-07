#include "FractalProvider.h"


/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Imported	 	*|
 \*-------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

/*----------------------------------------------------------------------*\
 |*			Implementation 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

/*-----------------*\
 |*	static	   *|
 \*----------------*/

FractalImage* FractalProvider::create()
    {

    int dw = 16 * 80; // =32*30=960
    int dh = 16 * 80; // =32*30=960

    //mendelbrot 1
      /*unsigned int nMin = 12;
      unsigned int nMax = 100;
      bool useJulia = false;
      double cx = 0;
      double cyi = 0;
      double x1 = -2.1;
      double y1 = -1.3;
      double x2 = 0.8;
      double y2 = 1.3;*/
    //julia 1

    unsigned int nMin = 52;
      unsigned int nMax = 100;
    bool useJulia = true;
    double cx = -0.12;
    double cyi = 0.85;
    double x1 = -1.3;
    double y1 = -1.4;
    double x2 = 1.3;
    double y2 = 1.4;

    //julia 5
    /*bool useJulia = true;
    unsigned int nMin = 50;
      unsigned int nMax = 150;
    double cx = -0.52;
    double cyi = 0.57;
    double x1 = -1.7;
    double x2 = 1.7;
    double y1 = -1.2;
    double y2 = 1.2;*/

      //julia 4
      /*
       * unsigned int nMin = 300;
      unsigned int nMax = 500;
       * useJulia = true;
      double cx = -0.745;
      double cyi = 0.1;
      double x1 = -1.7;
      double y1 = -1;
      double x2 = 1.7;
      double y2 = 1;*/



    return new FractalImage(dw, dh, nMin, nMax, cx, cyi, useJulia,x1,x2,y1,y2);
    }


/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/

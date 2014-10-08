#include "MandelbrotJuliaProvider.h"
#include "MathTools.h"
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

MandelbrotJuliaImage* MandelbrotJuliaProvider::create(void)
    {
    int dw = 16 * 60; // =32*30=960
    int dh = 16 * 60; // =32*30=960

    // Mandlebrot Exemple 1
  /*  bool isJulia=false;
    int n=24;
   double xMin=-2.1;
   double yMin=-1.3;
    double xMax=0.8;
    double yMax=1.3;
    double cX=0;
    double cY=0;*/

    //MandleBrot Exemple 2
   bool isJulia = false;
    int n = 600;
     double xMin =-1.3968;
      double xMax=-1.3578;

      double yMin=-0.03362;
      double yMax=0.0013973;
      double cX=0;
    double cY=0;


    // Julia Exemple 1
    /*  bool isJulia = true;
       int n = 52;
       double xMin = -1.3;
       double xMax=1.3;

       double yMin=-1.4;
       double yMax=1.4;

       double cX=-0.12;
       double cY=0.85;*/

       // Julia Exemple 2
          /* bool isJulia = true;
             int n = 52;
              double xMin =-0.327167 ;
              double xMax=-0.086667;

              double yMin=-0.2156;
              double yMax=0.0434;

              double cX=-0.12;
              double cY=0.85;*/

              // Julia Exemple 3
                   /* bool isJulia = true;
                     int n = 300;
                     double xMin = -1.7;
                     double xMax=1.7;

                     double yMin=-1;
                     double yMax=1;

                     double cX=-0.745;
                     double cY=0.1; */

                     // Julia Exemple 4
                          /*  bool isJulia = true;
                            int n = 50;
                            double xMin = -1.7;
                            double xMax=1.7;

                            double yMin=-1.2;
                            double yMax=1.2;

                            double cX=-0.52;
                            double cY=0.57;*/

    // animation para
    //float dt = 2 * PI / 400;
    float dt = 1;

    return new MandelbrotJuliaImage(dw, dh, dt, n,xMin,xMax,yMin,yMax,isJulia,cX,cY);
    }

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/

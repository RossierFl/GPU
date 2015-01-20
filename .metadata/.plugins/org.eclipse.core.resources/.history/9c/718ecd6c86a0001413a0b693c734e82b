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

MandelbrotJulia* MandelbrotJuliaProvider::create()
    {
    int dw = 16 * 60; // =32*30=960
    int dh = 16 * 60; // =32*30=960

    // Mandlebrot Exemple 1
  /*  bool isJulia=false;
    int n=24;
   float xMin=-2.1;
   float yMin=-1.3;
    float xMax=0.8;
    float yMax=1.3;
    float cX=0;
    float cY=0;*/

    //MandleBrot Exemple 2
  /* bool isJulia = false;
    int n = 600;
     float xMin =-1.3968;
      float xMax=-1.3578;

      float yMin=-0.03362;
      float yMax=0.0013973;
      float cX=0;
    float cY=0;*/


    // Julia Exemple 1
      bool isJulia = true;
       int n = 52;
       float xMin = -1.3;
       float xMax=1.3;

       float yMin=-1.4;
       float yMax=1.4;

       float cX=-0.12;
       float cY=0.85;

       // Julia Exemple 2
          /* bool isJulia = true;
             int n = 52;
              float xMin =-0.327167 ;
              float xMax=-0.086667;

              float yMin=-0.2156;
              float yMax=0.0434;

              float cX=-0.12;
              float cY=0.85;*/

              // Julia Exemple 3
                   /* bool isJulia = true;
                     int n = 300;
                     float xMin = -1.7;
                     float xMax=1.7;

                     float yMin=-1;
                     float yMax=1;

                     float cX=-0.745;
                     float cY=0.1; */

                     // Julia Exemple 4
                          /*  bool isJulia = true;
                            int n = 50;
                            float xMin = -1.7;
                            float xMax=1.7;

                            float yMin=-1.2;
                            float yMax=1.2;

                            float cX=-0.52;
                            float cY=0.57;*/

    // animation para
    //float dt = 2 * PI / 400;
    float dt = 1;

    return new MandelbrotJulia(dw, dh, dt, n,xMin,xMax,yMin,yMax,isJulia,cX,cY);
    }

ImageFonctionel* MandelbrotJuliaProvider::createGL(void)
    {
    ColorRGB_01* ptrColorTitre=new ColorRGB_01(0,0,0);

    return new ImageFonctionel(create(),ptrColorTitre); // both ptr destroy by destructor of ImageFonctionel
    }

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/

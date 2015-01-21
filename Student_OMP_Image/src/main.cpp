#include <iostream>

#include "MathTools.h"
#include "GLUTImageViewers.h"

#include "RipplingProvider.h"
#include "MandelbrotJuliaProvider.h"
#include "ConvolutionProvider.h"

using std::cout;
using std::endl;

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Imported		*|
 \*-------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

int main(int argc, char** argv);

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

static int run(void);

/*----------------------------------------------------------------------*\
 |*			Implementation 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

int main(int argc, char** argv)
    {
    cout << "main" << endl;

    GLUTImageViewers::init(argc, argv); // call once

    return run(); // Bloquant, Tant qu'une fenetre est ouverte
    }

int run(void)
    {
    bool isAnimation = true;
    bool isSelectionEnable = false;

 //  RipplingImage* ptrRippling = RipplingProvider::create();
   ConvolutionImage* ptrConvolution = ConvolutionProvider::create();

   GLUTImageViewers convolutionViewer(ptrConvolution, isAnimation, isSelectionEnable, 20, 20);
 //  GLUTImageViewers ripplingViewer(ptrRippling, isAnimation, isSelectionEnable, 20, 20);
    // Insert here other viewers ...

  //  MandelbrotJuliaImage* prtMandelbrotJulia = MandelbrotJuliaProvider::create();
 //   isAnimation = true ;
  //  isSelectionEnable=false;
   // GLUTImageViewers mandelbrotJuliaViewer(prtMandelbrotJulia,isAnimation,isSelectionEnable,20,20);

    GLUTImageViewers::runALL(); // Bloquant, Tant qu'une fenetre est ouverte

    // destruction
	{
	//delete ptrRippling;
	delete ptrConvolution;
	//delete prtMandelbrotJulia;

	//ptrRippling = NULL;
	ptrConvolution = NULL;
	//prtMandelbrotJulia=NULL;
	}

    return EXIT_SUCCESS;
    }

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/


#include <iostream>
#include <stdlib.h>
#include <string.h>

#include "GLUTImageViewers.h"

#include "Device.h"
#include "cudaTools.h"

#include "Rippling0Provider.h"
#include "RipplingProvider.h"
#include "MandelbrotJuliaProvider.h"
#include "MandelbrotJuliaProviderMultiGPU.h"
#include "HeatTransfertProvider.h"
#include "RayTracingProvider.h"
#include "NewtonProvider.h"
#include "ConvolutionProvider.h"
#include "ConvolutionTextureProvider.h"

using std::cout;
using std::endl;
using std::string;

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Imported	 	*|
 \*-------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

void runConvolution (){
    //Image* ptrConvolution = ConvolutionProvider::createGL();
    Image* ptrConvolutionTexture = ConvolutionTextureProvider::createGL();
    bool isAnimation = true;
     bool isSelection = true;
     GLUTImageViewers convolutionTextureViewer(ptrConvolutionTexture, isAnimation, isSelection, 0, 0);
     GLUTImageViewers::runALL();
     {
	 delete ptrConvolutionTexture;
	 ptrConvolutionTexture=NULL;
     }
}

int mainGL(void);

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

/*----------------------------------------------------------------------*\
 |*			Implementation 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

int mainGL(void)
    {
   // Rippling0Image* ptrRippling0 = Rippling0Provider::createGL();
  //  Image* ptrRippling = RipplingProvider::createGL();
 //   Image* ptrRayTracing = RayTracingProvider::createGL();
 //   Image* ptrConvolution = ConvolutionProvider::createGL();
    // TODO : Insert  autres Images ...
    //ImageFonctionel* ptrMandelbrotJulia = MandelbrotJuliaProvider::createGL();

   // ImageFonctionel* ptrMandelbrotJuliaMultiGPU =  MandelbrotJuliaProviderMultiGPU::createGL();

 //  Image* ptrHeatTransfert =  HeatTransfertProvider::createGL();
   // ImageFonctionel* ptrNewton = NewtonProvider::createGL();


    bool isAnimation = true;
    bool isSelection = true;
    runConvolution();

   // GLUTImageViewers rippling0Viewer(ptrRippling0, isAnimation, isSelection, 0, 0);
    //GLUTImageViewers ripplingViewer(ptrRippling, isAnimation, isSelection, 0, 0);
    // TODO : Insert here autres ImageViewers ...
    //GLUTImageViewers mandelbrotJuliaViewer(ptrMandelbrotJulia, isAnimation, isSelection, 200, 20);

    //-----------------------------JULIA MANDELBROT MULTI GPU
 // GLUTImageViewers mandelbrotJuliaViewerMultiGPU(ptrMandelbrotJuliaMultiGPU, isAnimation, isSelection, 0, 0);
   //GLUTImageViewers heatTransfertViewer(ptrHeatTransfert, isAnimation, isSelection, 400, 40);
    //GLUTImageViewers  rayTracingViewer(ptrRayTracing, isAnimation, isSelection, 600, 60);
    //GLUTImageViewers  newtonViewer(ptrNewton, isAnimation, isSelection, 800, 80);
  //  GLUTImageViewers  convolutionViewer(ptrConvolution, isAnimation, isSelection, 1000, 100);
   // GLUTImageViewers::runALL(); // Bloquant, Tant qu'une fenetre est ouverte

    // destruction
	{
	//delete ptrRippling0;
	//delete ptrRippling;
	//delete ptrRayTracing;
	//delete ptrMandelbrotJuliaMultiGPU;
	//delete ptrMandelbrotJulia;
	//delete ptrHeatTransfert;
	//delete ptrNewton;
	//delete ptrConvolution;

	//ptrRippling0 = NULL;
	//ptrRayTracing=NULL;
	//ptrRippling = NULL;
	//ptrHeatTransfert=NULL;
	//ptrNewton=NULL;
	//ptrConvolution=NULL;
	//ptrMandelbrotJuliaMultiGPU=NULL;
	//ptrMandelbrotJulia = NULL;
	}

    return EXIT_SUCCESS;
    }

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/


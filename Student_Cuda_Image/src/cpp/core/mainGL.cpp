#include <iostream>
#include <stdlib.h>
#include <string.h>

#include "GLUTImageViewers.h"

#include "Device.h"
#include "cudaTools.h"

#include "Rippling0Provider.h"
#include "RipplingProvider.h"
#include "MandelbrotJuliaProvider.h"
#include "NewtonProvider.h"
#include "RayTracingProvider.h"
#include "HeatTransfertProvider.h"

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

int mainGL();

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

/*----------------------------------------------------------------------*\
 |*			Implementation 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

int mainGL()
{

	Image* ptrHeatTransfert = HeatTransfertProvider::createGL();
	//Rippling0Image* ptrRippling0 = Rippling0Provider::createGL();
	//Image* ptrRippling = RipplingProvider::createGL();
	//ImageFonctionel* ptrMandelbrotJulia = MandelbrotJuliaProvider::createGL();
	//ImageFonctionel* ptrNewton = NewtonProvider::createGL();
	//Image* ptrRayTracing = RayTracingProvider::createGL();

	bool isAnimation = true;
	bool isSelection = true;

	GLUTImageViewers heatTransfertViewer(ptrHeatTransfert, isAnimation, isSelection, 0, 0);
	//GLUTImageViewers rippling0Viewer(ptrRippling0, isAnimation, isSelection, 0, 0);
	//GLUTImageViewers ripplingViewer(ptrRippling, isAnimation, isSelection, 100, 0);
	//GLUTImageViewers mandelbrotJuliaViewer(ptrMandelbrotJulia, isAnimation, isSelection, 200, 0);
	//GLUTImageViewers newtonViewer(ptrNewton, isAnimation, isSelection, 300, 0);
	//GLUTImageViewers rayTracingViewer(ptrRayTracing, isAnimation, isSelection, 400, 0);


	GLUTImageViewers::runALL(); // Bloquant, Tant qu'une fenetre est ouverte

	// destruction
	{
		//delete ptrRippling0;
		//delete ptrRippling;
		//delete ptrMandelbrotJulia;
		//delete ptrNewton;
		//delete ptrRayTracing;
		delete ptrHeatTransfert;

		//ptrRippling0 = NULL;
		//ptrRippling = NULL;
		//ptrMandelbrotJulia = NULL;
		//ptrNewton = NULL;
		//ptrRayTracing = NULL;
		ptrHeatTransfert = NULL;
	}

	return EXIT_SUCCESS;
}

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/


#include <iostream>

#include "cudaTools.h"
#include "Device.h"
#include "MathTools.h"

#include "Chronos.h"

using std::cout;
using std::endl;

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Imported		*|
 \*-------------------------------------*/

extern void launchKernelVague0(uchar4* ptrDevPixels, int w, int h, float t);

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

int vague0FreeGL(int itmax=1000);

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

/*----------------------------------------------------------------------*\
 |*			Implementation 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

/**
 * Hyp: itmax suffisamment grand pour que timeElapse soit significatif
 */
int vague0FreeGL(int itmax)
    {
    cout<<"\n[Vague0] : FreeGL running ..."<<endl;

    int h = 16 * 60;
    int w = h;

    uchar4* ptrDevImage;
    size_t size = w * h * sizeof(uchar4);
    HANDLE_ERROR(cudaMalloc((void**) &ptrDevImage, size));
    HANDLE_ERROR(cudaMemset(ptrDevImage, 0, size));

    int i = 0;
    float t = 0;
    float dt = 2 * PI / 10000;
    Chronos chrono;

    while (i < itmax)
	{
	launchKernelVague0(ptrDevImage, w, h, t); // assynchrone!
	Device::checkKernelError("Vague0");
	Device::synchronize(); // Important!

	t += dt;
	i++;
	}

    chrono.stop();
    HANDLE_ERROR(cudaFree(ptrDevImage));

    double timeElapseS = chrono.getDeltaTime();
    int fps = itmax / timeElapseS;

    cout<<"fps : "<<fps<<endl;

    return fps;
    }

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/


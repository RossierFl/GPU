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

extern void launchKernelRippling0(uchar4* ptrDevPixels, int w, int h, float t);

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

int rippling0FreeGL(int itmax);

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
int rippling0FreeGL(int itmax)
    {
    cout<<"\n[Rippling0] : FreeGL running ..."<<endl;

    int h = 16 * 60;
    int w = h;

    uchar4* ptrDevImage;
    size_t size = w * h * sizeof(uchar4);
    HANDLE_ERROR(cudaMalloc((void**) &ptrDevImage, size));
    HANDLE_ERROR(cudaMemset(ptrDevImage, 0, size));

    int i = 0;
    float t = 0;
    float dt = 2 * PI / 10;
    Chronos chrono;

    while (i < itmax)
	{
	launchKernelRippling0(ptrDevImage, w, h, t);
	Device::checkKernelError("Rippling0");
	Device::synchronize();

	t += dt;
	i++;
	}

    chrono.stop();
    HANDLE_ERROR(cudaFree(ptrDevImage));

    double timeElapseS = chrono.getDeltaTime();
    int fps = itmax / timeElapseS;

    cout << "fps : "<<fps<<endl;

    return fps;
    }

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/


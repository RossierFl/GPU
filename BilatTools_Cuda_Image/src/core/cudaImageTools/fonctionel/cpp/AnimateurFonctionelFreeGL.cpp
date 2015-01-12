#include <iostream>

#include "cudaTools.h"
#include "Device.h"
#include "MathTools.h"
#include "StringTools.h"

#include "Chronos.h"

#include "AnimateurFonctionelFreeGL.h"

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

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

/*----------------------------------------------------------------------*\
 |*			Implementation 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

AnimateurFonctionelFreeGL::AnimateurFonctionelFreeGL(AnimableFonctionel_I* ptrAnimable, int nbIteration)
    {
    // Input
    this->nbIteration = nbIteration;
    this->ptrAnimable = ptrAnimable;

    // Outputs
    this->fps = -1;
    this->timeElapseS = -1;

    start();
    printStat();
    }

AnimateurFonctionelFreeGL::~AnimateurFonctionelFreeGL()
    {
    delete ptrAnimable; // discutable!
    }

int AnimateurFonctionelFreeGL::getFps(void)
    {
    return fps;
    }

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

int AnimateurFonctionelFreeGL::start()
    {
    cout << "\n[AnimateurFreeGL] : started : " << ptrAnimable->getTitle() << endl;

    int w = ptrAnimable->getW();
    int h = ptrAnimable->getH();
    size_t size = w * h * sizeof(uchar4);

    uchar4* ptrDevImage;
    HANDLE_ERROR(cudaMalloc((void**) &ptrDevImage, size));
    HANDLE_ERROR(cudaMemset(ptrDevImage, 0, size));

    int i = 0;
    Chronos chrono;

    DomaineMath* ptrDomaineMath=ptrAnimable->getDomaineMathInit();
    const char* messageError=ptrAnimable->getTitle().c_str();
    while (i < nbIteration)
	{
	ptrAnimable->runGPU(ptrDevImage,*ptrDomaineMath);

	Device::checkKernelError(messageError);
	Device::synchronize(); // Important!

	ptrAnimable->animationStep();

	i++;
	}

    chrono.stop();
    HANDLE_ERROR(cudaFree(ptrDevImage));

    this->timeElapseS = chrono.getDeltaTime();
    this->fps = nbIteration / timeElapseS;

    return fps;
    }

void AnimateurFonctionelFreeGL::printStat()
    {
    cout << endl;
    cout << "Benchmark   : [" << ptrAnimable->getTitle()<<"]"  << endl;
    cout << "#Iteration  : " << nbIteration << endl;
    cout << "#secondes   : " << timeElapseS << " (s)" << endl;
    cout << "#fps        : " << fps << endl;
    }

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/


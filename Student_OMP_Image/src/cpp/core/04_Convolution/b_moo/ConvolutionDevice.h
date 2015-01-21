#ifndef CONVOLUTIONDEVICE_H_
#define CONVOLUTIONDEVICE_H_

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

#include <iostream>
#include <omp.h>
#include "IndiceTools.h"
#include "OmpTools.h"
#include "cudaType.h"


/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

class ConvolutionDevice
    {
    public:
	ConvolutionDevice();
	virtual ~ConvolutionDevice();

	void colorToGreyTexture(uchar4* ptrDevPixels, int w, int h);

	void affineTransformTexture(uchar4* ptrDevPixels, float a, float b, int w, int h, int offset);

	void convolutionTextureKernel(uchar4* ptrDevPixels,float* ptrKernel ,int k, int w, int h, float t);

	void findMinMaxTexture(uchar4* ptrDevPixels, uchar* ptrDevResult, int w, int h);

    private:

	void ecrasementTexture(uchar* tabSM, int halfThread);

	void reductionIntraBTexture(uchar* tabSM);

	void reductionInterBTexture(uchar* tabSM, uchar* ptrDevResult);

	void reductionIntraTTexture(uchar* tabSM, uchar4* ptrDevPixels, int n);

    };

#endif 

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/

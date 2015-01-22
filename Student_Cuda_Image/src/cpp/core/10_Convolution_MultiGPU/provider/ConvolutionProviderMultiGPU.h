#ifndef CONVOLUTIONPROVIDERMULTIGPU_H_
#define CONVOLUTIONPROVIDERMULTIGPU_H_

#include "ConvolutionMultiGPU.h"
#include "Image.h"

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

class ConvolutionProviderMultiGPU
    {
    public:

	static ConvolutionMultiGPU* create(void);
	static Image* createGL(void);


    };

#endif 

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/

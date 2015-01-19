#ifndef CONVOLUTIONPROVIDERSHARED_H_
#define CONVOLUTIONPROVIDERSHARED_H_

#include "ConvolutionShared.h"
#include "Image.h"

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

class ConvolutionProviderShared
    {
    public:

	static ConvolutionShared* create(void);
	static Image* createGL(void);


    };

#endif 

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/

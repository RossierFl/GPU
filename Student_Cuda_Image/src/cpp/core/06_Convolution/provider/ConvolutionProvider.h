#ifndef CONVOLUTIONPROVIDER_H_
#define CONVOLUTIONPROVIDER_H_

#include "Convolution.h"
#include "Image.h"

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

class ConvolutionProvider
    {
    public:

	static Convolution* create(void);
	static Image* createGL(void);


    };

#endif 

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/

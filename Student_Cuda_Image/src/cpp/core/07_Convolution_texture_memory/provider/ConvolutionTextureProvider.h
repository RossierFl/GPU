#ifndef CONVOLUTION_TEXTURE_PROVIDER_H_
#define CONVOLUTION_TEXTURE_PROVIDER_H_

#include "ConvolutionTexture.h"
#include "Image.h"

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

class ConvolutionTextureProvider
    {
    public:

	static ConvolutionTexture* create(void);
	static Image* createGL(void);


    };

#endif 

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/

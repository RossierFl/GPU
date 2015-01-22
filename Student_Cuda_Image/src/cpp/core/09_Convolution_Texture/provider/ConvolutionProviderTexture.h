#ifndef CONVOLUTIONPROVIDERTEXTURE_H_
#define CONVOLUTIONPROVIDERTEXTURE_H_

#include "ConvolutionTexture.h"
#include "Image.h"

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

class ConvolutionProviderTexture
    {
    public:

	static ConvolutionTexture* create(void);
	static Image* createGL(void);


    };

#endif 

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/

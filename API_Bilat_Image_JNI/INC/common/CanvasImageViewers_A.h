#ifndef CANVAS_IMAGE_VIEWER_A_H_
#define CANVAS_IMAGE_VIEWER_A_H_

#include "envImageJNI.h"
#include "CanvasImageNative.h"
#include "GLImages_A.h"
#include "ImageMOOs_I.h"

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

class CBI_IMAGE_JNI CanvasImageViewers_A
    {
	/*--------------------------------------*\
	 |*		Constructor		*|
	 \*-------------------------------------*/

    public:

	CanvasImageViewers_A();

	virtual ~CanvasImageViewers_A();

	/*--------------------------------------*\
	 |*		Methodes		*|
	 \*-------------------------------------*/

    public:

	int getCanvasNativeID();

	ImageMOOs_I* getImageMOO();

	GLImages_A* getGLImage();

	CanvasImageNative* getCanvasImageNative();

    protected:

	/**
	 * Instancie un CanvasImageNative avec la ptrGLImage
	 */
	void setGLImage(GLImages_A* ptrGLImage);

	/*--------------------------------------*\
	 |*		Attributs		*|
	 \*-------------------------------------*/

    private:

	// Tools
	GLImages_A* ptrGLImage;
	CanvasImageNative* ptrCanvasNativeImage;
    };

#endif 

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/

#ifndef CANVAS_IMAGE_NATIVE_H
#define CANVAS_IMAGE_NATIVE_H

#include "envImageJNI.h"
#include "ImageMOOs_I.h"
#include "GLImages_A.h"
#include "CanvasNative.h"

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

class CBI_IMAGE_JNI  CanvasImageNative: public CanvasNative
    {
    public:
	/*--------------------------------------*\
	 |*		Constructor		*|
	 \*-------------------------------------*/

	CanvasImageNative(GLImages_A* ptrGLImage);

	/*--------------------------------------*\
	 |*		Destructor		*|
	 \*-------------------------------------*/

	virtual ~CanvasImageNative();

	/*--------------------------------------*\
	 |*		Methodes		*|
	 \*-------------------------------------*/

    protected:

	/**
	 * Override
	 */
	virtual void onPaintGL(JNIEnv *env, jobject panel);

	/*--------------------------------------*\
	 |*		Get			*|
	 \*-------------------------------------*/

    public :

	GLImages_A* getGLImage();

	ImageMOOs_I* getImageMOO();

    };

#endif 

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/

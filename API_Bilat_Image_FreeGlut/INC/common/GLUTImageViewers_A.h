#ifndef GLUT_IMAGE_VIEWERS_A_H_
#define GLUT_IMAGE_VIEWERS_A_H_

#include "envImage_FreeGlut.h"
#include "GLUTWindowImage.h"
#include "ImageMOOs_I.h"

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

class CBI_IMAGE_FREE_GLUT GLUTImageViewers_A
    {

	/*--------------------------------------*\
	 |*		Constructor		*|
	 \*-------------------------------------*/

    protected:

	GLUTImageViewers_A();

    public:

	virtual ~GLUTImageViewers_A();

	/*--------------------------------------*\
 	|*		Methodes		*|
	 \*-------------------------------------*/

	static void init(int argc, char** argv);

	/**
	 * Attention appel bloquant !
	 */
	static void runALL();

	/*--------------------------------------*\
	 |*		Get			*|
	 \*-------------------------------------*/

	/**
	 * Cast to ImageMOOs or your ImageFonctionelMOOs_A
	 *
	 * Sample :
	 *
	 *  ImageMOOs_I* ptrImageMOO_A=this->getImageMOO();
	 *
	 *
	 *  ImageMOOs_A* ptrImageMOO=dynamic_cast<ImageMOOs_A*>(ptrImageMOO_A);
	 *
	 *  MyImageFonctionelMOO* ptrImageMOO=dynamic_cast<MyImageFonctionelMOO*>(ptrImageMOO_A);
	 *
	 *  MyImageMOOs ptrImageMOO=dynamic_cast<MyImageMOOs*>(ptrImageMOO_A);
	 *
	 *  http://www.cplusplus.com/doc/tutorial/typecasting/
	 */
	ImageMOOs_I* getImageMOO();

	GLUTWindowImage* getGLUTWindowImage();

	/*--------------------------------------*\
	 |*		Attributs		*|
	 \*-------------------------------------*/

    protected:
	// Tools
	GLUTWindowImage* ptrGLUTImageWindow;
    };

#endif 

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/

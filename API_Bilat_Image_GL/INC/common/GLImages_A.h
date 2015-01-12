#ifndef GLIMAGE_API_WINDOWS_H
#define GLIMAGE_API_WINDOWS_H

#ifdef _WIN32
#include <glew.h>
#else
#include <GL/glew.h>
#endif

#include "envGLImage.h"
#include "ImageObserver_I.h"
#include "Displayable_A.h"
#include "GLPrimitiveDrawers.h"
#include "Graphic2Ds.h"

#include <string>
using std::string;

#include <vector>
using std::vector;

#include "ImageMOOs_I.h"

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

class CBI_GLIMAGE GLImages_A: public Displayable_A, public KeyListener_I, public MouseListener_I, public ImageObserver_I
    {

	/*--------------------------------------*\
	 |*		Constructor		*|
	 \*-------------------------------------*/

    public:

	GLImages_A(ImageMOOs_I* ptrImageMOO, bool isAnimationEnable = true);

	/*--------------------------------------*\
	 |*		Destructor		*|
	 \*-------------------------------------*/

    public:

	virtual ~GLImages_A();

	/*--------------------------------------*\
	 |*		Methodes		*|
	 \*-------------------------------------*/

    public:

	virtual void init(Panel_A &panel);

	virtual void reshape(Panel_A &panel, int w, int h);

	virtual void display(Panel_A &panel);

	virtual void release(Panel_A &panel);

	virtual void onKeyPressed(const KeyEvent &event);

	virtual void onMouseMoved(const MouseEvent &event);

	virtual void onMousePressed(const MouseEvent &event);

	virtual void onMouseReleased(const MouseEvent &event);

	virtual void onMouseWheel(const MouseWheelEvent &event);

	virtual void onImageUpdate();

    protected:

	virtual void fillPBO()=0;

	virtual void drawPrimitives(Panel_A &panel);

	virtual void createPBO();

	virtual void createTexture();

	void drawTexture();

	void deleteTexture();

	void drawCredits(Panel_A &panel);

    private:

	/**
	 * Update view from model, still need to manualy repaint the Window
	 */
	void updateView();

	void toImageSpaceCoordinate(int x, int y, int &imageX, int &imageY);

	/*--------------------------------------*\
	 |*		Get			*|
	 \*-------------------------------------*/
    public:
	/**
	 * width of the  frame
	 */
	int getDxFrame();

	/**
	 * height of the  frame
	 */
	int getDyFrame();

	ImageMOOs_I* getImageMOO();

    protected:

	GLuint getPboID();

	GLuint getTextureID();

	/*--------------------------------------*\
	 |*		Is			*|
	 \*-------------------------------------*/

    public:

	bool isAnimationEnable() const;

	/*--------------------------------------*\
	 |*		Set			*|
	 \*-------------------------------------*/

    public:

	void setAnimationEnable(bool isEnable);

	/*--------------------------------------*\
	 |*		Attributs		*|
	 \*-------------------------------------*/

    protected:

	// Inputs
	ImageMOOs_I* ptrImageMOO;
	bool animationEnable;
	int dxFrame;
	int dyFrame;

	// OpenGL
	GLPrimitiveDrawers glPrimitiveDrawer;
	Graphic2Ds graphique2D;
	GLuint textureID;
	GLuint pbo;
    };

#endif

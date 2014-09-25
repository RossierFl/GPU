#ifndef CANVAS_NATIVE_H
#define CANVAS_NATIVE_H
#include "envCanvasJNI.h"
#include "Displayable_A.h"
#include "Panel_A.h"
#include "Context.h"
#include <atomic>
#include <jni.h>

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

class CBI_CANVAS_JNI CanvasNative: public Panel_A
    {
	/*--------------------------------------*\
	 |*		Constructor		*|
	 \*-------------------------------------*/

    public:
	CanvasNative(Displayable_A* ptrDisplayable);

	virtual ~CanvasNative();

	/*--------------------------------------*\
	 |*		Methodes		*|
	 \*-------------------------------------*/

    public:

	virtual void init(JNIEnv *env, jobject canvas);

	virtual void reshape(int w, int h, JNIEnv *env, jobject canvas);

	virtual void display(JNIEnv *env, jobject canvas);

	virtual void release(JNIEnv *env, jobject canvas);

	virtual void onKeyPressed(const KeyEvent &keyEvent, JNIEnv *env, jobject canvas);

	virtual void onMousePressed(const MouseEvent &e, JNIEnv *env, jobject canvas);

	virtual void onMouseReleased(const MouseEvent &e, JNIEnv *env, jobject canvas);

	virtual void onMouseMoved(const MouseEvent &e, JNIEnv *env, jobject canvas);

	virtual void onMouseWheel(const MouseWheelEvent &e, JNIEnv *env, jobject canvas);

    protected:

	virtual void onPaintGL(JNIEnv *env, jobject canvas);

	void repaint(JNIEnv *env, jobject canvas);

	/*--------------------------------------*\
	 |*		Get			*|
	 \*-------------------------------------*/
    public:

	virtual TextRenderer_A* getTextRenderer()
	    {
	    return txtRender;
	    }

	virtual FontLoader_A* getFontLoader()
	    {
	    return fontLoader;
	    }

	Displayable_A* getDisplayable()
	    {
	    return ptrDisplayable;
	    }

	inline int getID() const
	    {
	    return id;
	    }

	/*--------------------------------------*\
	 |*		Set			*|
	 \*-------------------------------------*/
    public:
	inline void setID(int id)
	    {
	    this->id = id;
	    }

    private:

	//Inputs
	Displayable_A* ptrDisplayable;

	// Tools
	int id;
	TextRenderer_A* txtRender;
	FontLoader_A* fontLoader;
	bool isInit;
	Context* ptrContext;

	static std::atomic_int ID_COUNTER;
    };

#endif 

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/

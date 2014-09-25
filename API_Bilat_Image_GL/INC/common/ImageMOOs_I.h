#ifndef IMAGEMOOS_A_H
#define IMAGEMOOS_A_H

#include "envGLImage.h"
#include "KeyListener_I.h"
#include "MouseListener_I.h"
#include "ImageObserver_I.h"
#include "Graphic2Ds.h"

#include <iostream>
#include <string>
#include <vector>

using std::vector;
using std::string;
using std::ostream;

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

/**
 * Base class for Image Model.
 */
class CBI_GLIMAGE ImageMOOs_I
    {

	/*--------------------------------------*\
	 |*		Constructor		*|
	 \*-------------------------------------*/
    public:
	ImageMOOs_I(unsigned int width, unsigned int height);

	ImageMOOs_I(const ImageMOOs_I &imageSource);

	/*--------------------------------------*\
	 |*		Destructor		*|
	 \*-------------------------------------*/
    public:
	virtual ~ImageMOOs_I();

	/*--------------------------------------*\
	 |*		Methodes		*|
	 \*-------------------------------------*/
    public:
	/**
	 * A redefinir par l'utilisateur
	 */
	virtual void animationStep(bool& isNeedUpdateView)=0;

	/**
	 * A redefinir par l'utilisateur
	 */
	virtual void paintPrimitives(Graphic2Ds& ptrGraphic2D)=0;

	/**
	 * call by API
	 */
	virtual void animationStepAPI(bool& isNeedUpdateView);

	/**
	 * call by API
	 */
	virtual void paintPrimitivesAPI(Graphic2Ds& ptrGraphic2D);

	virtual void print(ostream& stream) const;

	void registerImageObserver(ImageObserver_I &ptrObserver);

	void unregisterImageObserver(ImageObserver_I &ptrObserver);

	/*
	 * Notify all registred ImageObserver_I
	 * @see registerImageObserver
	 */
	void update() const;

	/*--------------------------------------*\
	 |*		Set			*|
	 \*-------------------------------------*/
    public:

	void setKeyListener(KeyListener_I* ptrKeyListener);

	void setMouseListener(MouseListener_I* ptrMouseListener);

	/*--------------------------------------*\
	 |*		Get			*|
	 \*-------------------------------------*/

    public:

	inline unsigned int getW() const
	    {
	    return width;
	    }

	inline unsigned int getH() const
	    {
	    return height;
	    }

	inline KeyListener_I* getKeyListener() const
	    {
	    return ptrKeyListener;
	    }

	inline MouseListener_I* getMouseListener() const
	    {
	    return ptrMouseListener;
	    }

	unsigned int getSizeOctet() const;

	/*--------------------------------------*\
	 |*		Friend			*|
	 \*-------------------------------------*/

	/**
	 * call image.print(stream)
	 */
	CBI_GLIMAGE
	friend ostream& operator<<(ostream& stream, const ImageMOOs_I& image);

	/*--------------------------------------*\
	 |*		Attributs		*|
	 \*-------------------------------------*/

    private:
	// Inputs
	unsigned int width;
	unsigned int height;

	// Tools
	KeyListener_I* ptrKeyListener;
	MouseListener_I* ptrMouseListener;
	vector<ImageObserver_I*> vectorObservable;

    };

#endif

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/

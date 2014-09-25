#ifndef GLUT_WINDOW_CUSTOMISER_A_H
#define GLUT_WINDOW_CUSTOMISER_A_H

#include "envFreeGlutTools.h"
#include "Panel_A.h"
#include "GLConfig.h"
#include "Displayable_A.h"
#include <thread> //requier compilation flags -std=c++0x
#include <string>

using std::string;
using std::thread;

#define DEFAULT_GLUT_DISPLAY_MODE GLUT_DOUBLE|GLUT_DEPTH|GLUT_RGBA

/**
 * Etat d'une GLUTWindow
 * A un instant t, elle ne peux avoir qu'un seul �tat, soit CREATED,RUNNING ou DESTROYED.
 * L'�tat NOT_CREATED est utiliser � la construction de l'objet et fait office d'�tat "NULL" ou sans �tat
 */
enum GLUT_WINDOW_CUSTOMISER_STATE
    {
    NOT_CREATED,
    CREATED,
    RUNNING,
    DESTROYED
    };

/**
 * But :
 * 	Permet de customiser une fenetre  FreeGLUT.
 *
 * Note :
 *
 * 	Seul les methodes init et display sont obligatoire.
 *
 * Attention :
 *
 * 	la fonction idleFun est appel� de mani�re fr�n�tique ! A utiliser a vos risque et p�rile.
 */
class CBI_FREEGLUT_TOOLS GLUTWindow: public Panel_A
    {
    public:
	/*--------------------------------------*\
	 |*		Constructor		*|
	 \*-------------------------------------*/

	GLUTWindow(Displayable_A* ptrDisplayable, string title, int width, int height, int pxFrame = 0, int pyFrame = 0, int glutDisplayMode =
	DEFAULT_GLUT_DISPLAY_MODE);

	/*--------------------------------------*\
	 |*		Destructor		*|
	 \*-------------------------------------*/

	virtual ~GLUTWindow();

	/*--------------------------------------*\
	 |*		Callbacks		*|
	 \*-------------------------------------*/

	virtual void display(void);
	virtual void release(void);
	virtual void reshape(int w, int h);
	virtual void mouseMoved(int x, int y);
	virtual void mouseWheelChanged(int wheel, int direction, int x, int y);
	virtual void mousePressed(int button, int state, int x, int y);
	virtual void keyPressed(unsigned char key, int x, int y);
	virtual void specialKeyPressed(int key, int x, int y);
	virtual void closeWindow();

	/**
	 * PostRendu est appeler apres GLUTWindowManager::runALL.
	 *
	 * Elle est dans son propre thread. (un thread par fen�tre).
	 *
	 * GLUTWindow ne stop pas le thread explicitement. Donc si il y a une boucle infinie, il faut utiliser l'etat de la fenetre comme crit�re d'arret.
	 *
	 * Par exemple
	 *
	 * 	isDestroyed
	 * 	isRunning
	 *
	 *  Interuption du thread
	 *
	 *  	try
	 *	    {
	 * 	     ....
	 *   	    }
	 * 	catch (boost::thread_interrupted&)
	 *	    {
	 *	     ...
	 *	    }
	 */
	virtual void postRendu();

	/**
	 * Fonction appel� a chaque fois que glut n'a rien � faire dans la mainLoop.
	 * CaD s'il n'y a pas d'�venents utilisateur (souris,clavier,joystick,repaint,etc...)
	 */
	virtual void idleFunc();

	/*--------------------------------------*\
	 |*		Methodes		*|
	 \*-------------------------------------*/

	/**
	 * Don't Use !
	 * Only used by GLUTWindowManagers !
	 * Will start the postRenduThread
	 */
	void startWindow();

	/**
	 * call display()
	 */
	void repaint() const;

	/*--------------------------------------*\
	 |*		Get			*|
	 \*-------------------------------------*/

	int getFrameWidth(void) const;

	int getFrameHeight(void) const;

	int getFramePositionX(void) const;

	int getFramePositionY(void) const;

	int getGLUTDisplayMode(void) const;

	unsigned int getGLUTWindowID(void) const;

	string getTitle(void) const;

	Displayable_A* getPtrDisplayable();

	TextRenderer_A* getTextRenderer();

	FontLoader_A* getFontLoader();

	/*--------------------------------------*\
	 |*		Is			*|
	 \*-------------------------------------*/

	bool isRunning() const;

	bool isCreated() const;

	bool isDestroyed() const;

	bool isDisplaying() const;

	/*--------------------------------------*\
	 |*		Set			*|
	 \*-------------------------------------*/

	/**
	 * Don't Use !
	 * Only used by GLUTWindowManagers !
	 */
	void setState(GLUT_WINDOW_CUSTOMISER_STATE state);

	/*--------------------------------------*\
	 |*		Private			*|
	 \*-------------------------------------*/

    private:
	ModifierType getModifier();

	void startThreadPostRendu();

	/*--------------------------------------*\
	 |*		Attributs		*|
	 \*-------------------------------------*/

    private:

	// Input
	Displayable_A* ptrDisplayable;
	string title;
	int pxFrame;
	int pyFrame;
	int width;
	int height;
	int glutDisplayMode;

	//Tools
	TextRenderer_A* ptrTextRenderer;
	FontLoader_A* ptrFontLoader;
	int lastFPS;
	bool displaying;
	GLUT_WINDOW_CUSTOMISER_STATE state;
	unsigned int glutWindowId;

	// Animation
	thread threadPostRendu;
    };

#endif

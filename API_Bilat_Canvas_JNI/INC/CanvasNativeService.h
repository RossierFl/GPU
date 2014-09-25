#ifndef CANVAS_NATIVE_SERVICE_H
#define CANVAS_NATIVE_SERVICE_H
#include "envCanvasJNI.h"
#include "CanvasNative.h"
#include <map>

using std::map;

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/
/**
 * Singleton
 * Not thread Safe!
 */
class CBI_CANVAS_JNI CanvasNativeService
    {

	/*--------------------------------------*\
	 |*		Constructor		*|
	 \*-------------------------------------*/

    private:

	CanvasNativeService();

	CanvasNativeService(const CanvasNativeService& src);

	/*--------------------------------------*\
	 |*		Destructor		*|
	 \*-------------------------------------*/

    public:

	virtual ~CanvasNativeService();

	/*--------------------------------------*\
	 |*		Methodes		*|
	 \*-------------------------------------*/

    public:

	int registerCanvasNative(CanvasNative* ptrCanvasNative);

	void unregister(int id);

	/*--------------------------------------*\
	 |*		Get			*|
	 \*-------------------------------------*/

    public :

	CanvasNative* getCanvasNative(int id);

	static CanvasNativeService* getInstance();

	/*--------------------------------------*\
	 |*		Attributs		*|
	 \*-------------------------------------*/

    private:

	//Tools
	map<int, CanvasNative*> mapIdNativeCanvas;

	//Singleton
	static CanvasNativeService* INSTANCE;
    };

#endif 

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/

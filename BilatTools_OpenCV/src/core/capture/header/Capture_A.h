#ifndef CAPTURE_A_H_
#define CAPTURE_A_H_

#include <string>

#include <opencv.hpp>
#include <highgui.hpp>

#include "Chronos.h"
#include "cudaType.h"

using namespace cv;

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

/**
 * http://opencv.willowgarage.com/wiki/VideoCodecs
 */
class Capture_A
    {
	/*--------------------------------------*\
	|*		Constructor		*|
	 \*-------------------------------------*/

    public:

	Capture_A(VideoCapture* ptrCaptureStream,const string&  title, uchar4* ptrHostMemory=NULL);
	virtual ~Capture_A(void);

	/*--------------------------------------*\
	|*		Methodes		*|
	 \*-------------------------------------*/

    public:

	VideoCapture* getVideoCapture(void);
	int getW(void);
	int getH(void);
	string getTitle(void);
	Chronos getChronos(void);
	int fpsCapture(void);

	bool isOpened(void);
	int nbOctetImage(void);
	long nbCapture(void);

	virtual void printInfo(void);

	/**
	 * Temps a attendre entre 2 captures pour respecter fps original
	 */
	virtual int dtOriginalMS(void);

	/**
	 * To be call periodicly to obtain image
	 * Type pas RVBA, mais BVRA
	 */
	Mat capturer(void);

	// Tools
	static uchar4* castToUChar4(uchar* ptrTab);
	static uchar4* castToUChar4(Mat* ptrMap);

    protected:

	virtual void readStream(VideoCapture* ptrCaptureStream, Mat* ptrMatCaptureSrc)=0;

    private:


	/*--------------------------------------*\
	|*		Attributs		*|
	 \*-------------------------------------*/

    private:

	// Inputs
	string title;


	// Tools
	Mat matCaptureSrc;

	// Outputs
	float w;
	int h;
	Mat matCaptureDest;
	long compteurCapture;
	Chronos chrono;

    protected:
	VideoCapture* ptrCaptureStream;
    };

#endif

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/

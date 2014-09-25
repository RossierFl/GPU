#include <iostream>

#include "CaptureVideo.h"
#include "CaptureCamera.h"
#include "Capture_A.h"
#include "SequenceViewerCV.h"

using std::cout;
using std::cin;
using std::cerr;
using std::endl;
using std::string;

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Imported	 	*|
 \*-------------------------------------*/

extern int tuto(string nameVideo);

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

static int useVideo(void);
static int useCamera(void);
static int show(Capture_A* ptrCaptureur);
static string getVideoName(void);

/*----------------------------------------------------------------------*\
 |*			Implementation 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

int main(void)
    {
    cout << "main" << endl;

    //return tuto(getVideoName()); // debug

    bool isUseVideo = true;
    if (isUseVideo)
	{
	tuto(getVideoName()); // debug
	return useVideo();
	}
    else
	{
	return useCamera();
	}
    }

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

int useVideo(void)
    {
    cout << "use video" << endl;

    string title = "Tuto Video";
    string videoName = getVideoName();
    CaptureVideo captureur(getVideoName(), title);

    if (captureur.isOpened())
	{
	return show(&captureur); // bloquant
	}
    else
	{
	cerr << "\n[CBI] : Failed to open : " << videoName << endl;
	return EXIT_FAILURE;
	}
    }

string getVideoName(void)
    {
#ifdef _WIN32
    // Work
    // string nameVideo ="Q:\\neilPryde.avi";
   //  string nameVideo = "C:\\Users\\cedric.bilat\\Desktop\\neilPryde.avi"; // ok
      string nameVideo="C:\\Users\\cedric.bilat\\Desktop\\nasaFHD_short.avi"; //ok

    // Home
    //  string nameVideo = "C:\\Users\\bilat\\Desktop\\neilPryde.avi"; // ok
   //string nameVideo="C:\\Users\\bilat\\Desktop\\nasaFHD_short.avi";// ok
#else
    //string nameVideo = "/media/Data/Video//neilPryde.avi"; // ok
    string nameVideo = "/media/Data/Video/nasaFHD_short.avi"; // ok
#endif

    return nameVideo;
    }

int useCamera(void)
    {
    int idCamera = 0;
    string title = "Tuto Camera";

    // CaptureCamera captureur(idCamera, title,320,160);
    CaptureCamera captureur(idCamera, title);

    if (captureur.isOpened())
	{
	return show(&captureur);
	}
    else
	{
	return EXIT_FAILURE;
	}
    }

int show(Capture_A* ptrCaptureur)
    {
    SequenceVieverCV sequenceViever(ptrCaptureur);
    sequenceViever.run(); // bloquant
    return EXIT_SUCCESS;
    }

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/


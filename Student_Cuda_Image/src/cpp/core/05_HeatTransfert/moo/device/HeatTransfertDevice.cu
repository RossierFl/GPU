#include "Indice2D.h"
#include "IndiceTools.h"
#include "cudaTools.h"
#include "Device.h"
#include "CalibreurCudas.h"
#include "cstdio"

#include "HeatTransfertMath.h"

// Attention : 	Choix du nom est impotant!
//		HeatTransfertDevice.cu et non HeatTransfert.cu
// 		Dans ce dernier cas, probl�me de linkage, car le nom du .cu est le meme que le nom d'un .cpp (host)
//		On a donc ajouter Device (ou n'importequoi) pour que les noms soient diff�rents!

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

__global__ void heatTransfert(float* ptrDevImageAInput, float* ptrDevImageBOutput,int w, int h, float k);
__global__ void heatEcrasement(float* ptrDevImageInput,float* ptrDevImageHeaters ,float* ptrDevImageOutput,int w,int h);
__global__ void heatToScreenImageHSB(float* ptrDevImageInput, uchar4* ptrDevImageGL, int w, int h,CalibreurCudas calibreur);

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

/*----------------------------------------------------------------------*\
 |*			Implementation 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

//Diffusion
__global__ void heatTransfert(float* ptrDevImageAInput, float* ptrDevImageBOutput,int w, int h,float k)
    {
    HeatTransfertMath heatTransfertMath = HeatTransfertMath();

    const int TID = Indice2D::tid();
    const int NB_THREAD = Indice2D::nbThread();

    const int WH=w*h;

    float color;
    float colorSud;
    float colorEst;
    float colorNord;
    float colorOuest;

    int pixelI;
    int pixelJ;

    int s = TID;
    while (s < WH)
	{
	IndiceTools::toIJ(s, w, &pixelI, &pixelJ); // update (pixelI, pixelJ)
	if(pixelI!=0 && pixelJ!=0 && pixelI<h-1 && pixelJ<w-1){
	int sS = IndiceTools::toS(w,pixelI-1,pixelJ);
	int sE = IndiceTools::toS(w,pixelI,pixelJ+1);
	int sN = IndiceTools::toS(w,pixelI+1,pixelJ);
	int sO = IndiceTools::toS(w,pixelI,pixelJ-1);
	color=ptrDevImageAInput[s];
	colorSud = ptrDevImageAInput[sS];
	colorEst = ptrDevImageAInput[sE];
	colorNord= ptrDevImageAInput[sN];
	colorOuest = ptrDevImageAInput[sO];
	heatTransfertMath.calculeColorTransfert(&color,colorSud,colorEst,colorNord,colorOuest,k);
	//heatTransfertMath.colorIJ(&color,pixelI, pixelJ, t); 	// update color
	ptrDevImageBOutput[s] = color;
	}

	s += NB_THREAD;
	}
    }

//Ecrasement entre les heater et le résulat des diffusion
__global__ void heatEcrasement(float* ptrDevImageInput,float* ptrDevImageHeaters ,float* ptrDevImageOutput,int w,int h)
    {
    HeatTransfertMath heatTransfertMath = HeatTransfertMath();

    const int TID = Indice2D::tid();
    const int NB_THREAD = Indice2D::nbThread();
    const int WH = w*h;

    int s = TID;
    while (s < WH)
	{
	//IndiceTools::toIJ(s, w, &pixelI, &pixelJ); // update (pixelI, pixelJ)

	if(ptrDevImageHeaters[s]>0){
	    ptrDevImageOutput[s] = ptrDevImageHeaters[s];
	}else{
	    ptrDevImageOutput[s] = ptrDevImageInput[s];
	}


	s += NB_THREAD;
	}
    }


//Ecrasement entre les heater et le résulat des diffusion
__global__ void heatToScreenImageHSB(float* ptrDevImageInput, uchar4* ptrDevImageGL, int w, int h,CalibreurCudas calibreur)
    {
    HeatTransfertMath heatTransfertMath = HeatTransfertMath();

    const int TID = Indice2D::tid();
    const int NB_THREAD = Indice2D::nbThread();

    const int WH=w*h;

    uchar4 color;

    int pixelI;
    int pixelJ;

    int s = TID;
    while (s < WH)
	{
	IndiceTools::toIJ(s, w, &pixelI, &pixelJ); // update (pixelI, pixelJ)

	heatTransfertMath.convertFloatToColor(&calibreur,ptrDevImageInput[s],&color);	// update color
	ptrDevImageGL[s] = color;

	s += NB_THREAD;
	}
    }

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/


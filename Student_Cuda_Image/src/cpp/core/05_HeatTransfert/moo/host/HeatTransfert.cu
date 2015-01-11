#include <iostream>
#include <assert.h>

#include "HeatTransfert.h"
#include "Device.h"
#include "MathTools.h"
#include "CalibreurCudas.h"

using std::cout;
using std::endl;

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Imported	 	*|
 \*-------------------------------------*/

extern __global__ void heatTransfert(float* ptrDevImageAInput, float* ptrDevImageBOutput,int w, int h, float k);
extern __global__ void heatEcrasement(float* ptrDevImageInput,float* ptrDevImageHeaters ,float* ptrDevImageOutput,int w,int h);
extern __global__ void heatToScreenImageHSB(float* ptrDevImageInput, uchar4* ptrDevImageGL, int w, int h,CalibreurCudas calibreur);

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

/*----------------------------------------------------------------------*\
 |*			Implementation 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

/*-------------------------*\
 |*	Constructeur	    *|
 \*-------------------------*/

HeatTransfert::HeatTransfert(int w, int h, float dt, float k)
    {
    // Inputs
    this->w = w;
    this->h = h;
    this->dt = dt;
    this->k = k;

    // Tools
    this->dg = dim3(8, 8, 1); // disons a optimiser
    this->db = dim3(16, 16, 1); // disons a optimiser
    this->t = 0;
    this->iteration_aveugle_counter=0;

    //Outputs
    this->title = "[API Image Cuda] : HeatTransfert CUDA";

    // Check:
    //print(dg, db);
    Device::assertDim(dg, db);
    assert(w == h);

    cout << endl << "[CBI] HeatTransfert dt =" << dt;

    initGPUMemory(h,w);
    createDataForGPU(h, w);
    initGPUFirstStep(h, w, k);

    }

HeatTransfert::~HeatTransfert()
    {
    freeGPUMemory();
    }

/*-------------------------*\
 |*	Methode		    *|
 \*-------------------------*/

/**
 * Override
 * Call periodicly by the API
 */
void HeatTransfert::animationStep()
    {
    t += dt;
    }

/**
 * Override
 */
void HeatTransfert::runGPU(uchar4* ptrDevPixels)
    {
    CalibreurCudas calibreur = CalibreurCudas(0.0f,1.0f,0.7f,0.0f);
    iteration_aveugle_counter++;
  /*  heatTransfert<<<dg,db>>>( ptrImageDeviceA,ptrImageDeviceA, w, h,k);
       Device::synchronize();*/

    heatTransfert<<<dg,db>>>( ptrImageDeviceA,ptrImageDeviceB, w, h,k);
    Device::synchronize();
    heatEcrasement<<<dg,db>>>( ptrImageDeviceB, prtImageHeats , ptrImageDeviceB, w, h);
    Device::synchronize();
    heatTransfert<<<dg,db>>>( ptrImageDeviceB,ptrImageDeviceA, w, h,k);
    Device::synchronize();
    heatEcrasement<<<dg,db>>>( ptrImageDeviceA, prtImageHeats , ptrImageDeviceA, w, h);
    Device::synchronize();


    if (iteration_aveugle_counter == NB_ITERATION_AVEUGLE)
	{
	heatToScreenImageHSB<<<dg,db>>>( ptrImageDeviceA, ptrDevPixels, w, h,calibreur);
	Device::synchronize();
	iteration_aveugle_counter = 0;
	}
    }

/*--------------*\
 |*	get	 *|
 \*--------------*/

/**
 * Override
 */
float HeatTransfert::getT(void)
    {
    return t;
    }

/**
 * Override
 */
int HeatTransfert::getW(void)
    {
    return w;
    }

/**
 * Override
 */
int HeatTransfert::getH(void)
    {
    return h;
    }

/**
 * Override
 */
string HeatTransfert::getTitle(void)
    {
    return title;
    }

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

//Init GPU Memory and copy data
void HeatTransfert::initGPUMemory(int h, int w)
    {
    const int SIZE_IMAGE = h * w * sizeof(float);
    HANDLE_ERROR(cudaMalloc(&ptrImageDeviceA, SIZE_IMAGE));
    HANDLE_ERROR(cudaMemset(ptrImageDeviceA, 0, SIZE_IMAGE));
    HANDLE_ERROR(cudaMalloc(&ptrImageDeviceB, SIZE_IMAGE));
    HANDLE_ERROR(cudaMemset(ptrImageDeviceB, 0, SIZE_IMAGE));
    HANDLE_ERROR(cudaMalloc(&prtImageHeats, SIZE_IMAGE));
    HANDLE_ERROR(cudaMemset(prtImageHeats, 0, SIZE_IMAGE));
    }

void HeatTransfert::createDataForGPU(int h, int w)
    {
    const int SIZE_IMAGE = h * w * sizeof(float);
    float tableHostHeat[h][w];
    for (int i = 0; i < h; i++)
	{
	for (int j = 0; j < w; j++)
	    {
	    if (j > 179 && j < 195 && i > 179 && i < 195)
		{		//Gros carré froids
		tableHostHeat[i][j] = 0.2f;
		}
	    else if (j > 605 && j < 621 && i > 179 && i < 195)
		{
		tableHostHeat[i][j] = 0.2f;
		}
	    else if (j > 179 && j < 195 && i > 605 && i < 121)
		{
		tableHostHeat[i][j] = 0.2f;
		}
	    else if (j > 605 && j < 621 && i > 605 && i < 121)
		{
		tableHostHeat[i][j] = 0.2f;
		}
	    else if (j > 295 && j < 400 && i > 295 && i < 400)
		{ // Petits carrés froids
		tableHostHeat[i][j] = 0.2f;
		}
	    else if (j > 400 && j < 295 && i > 400 && i < 295)
		{
		tableHostHeat[i][j] = 0.2f;
		}
	    else if (j > 505 && j < 400 && i > 505 && i < 400)
		{
		tableHostHeat[i][j] = 0.2f;
		}
	    else if (j > 400 && j < 505 && i > 400 && i < 505)
		{
		tableHostHeat[i][j] = 0.2f;
		}
	    else if (j > 300 && j < 500 && i > 300 && i < 500)
		{ //Gros carré chaud
		tableHostHeat[i][j] = 1.0f;
		}
	    else
		{
		tableHostHeat[i][j] = 0;
		}
	    }
	}

    HANDLE_ERROR(cudaMemcpy(prtImageHeats, tableHostHeat, SIZE_IMAGE, cudaMemcpyHostToDevice)); //barriere implicite de sync
    }

void HeatTransfert::initGPUFirstStep(int h, int w, float k)
    {


   /* heatEcrasement<<<dg,db>>>(ptrImageDeviceB,prtImageHeats ,ptrImageDeviceA, w, h);
        Device::synchronize();*/


    heatEcrasement<<<dg,db>>>(ptrImageDeviceB,prtImageHeats ,ptrImageDeviceB, w, h);
    Device::synchronize();
    heatTransfert<<<dg,db>>>(ptrImageDeviceB,ptrImageDeviceA, w, h,k);
    Device::synchronize();
    heatEcrasement<<<dg,db>>>(ptrImageDeviceA,prtImageHeats ,ptrImageDeviceA, w, h);
    Device::synchronize();

    }

void HeatTransfert::freeGPUMemory()
    {
    HANDLE_ERROR(cudaFree(ptrImageDeviceA));
    HANDLE_ERROR(cudaFree(ptrImageDeviceB));
    HANDLE_ERROR(cudaFree(prtImageHeats));
    }

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/

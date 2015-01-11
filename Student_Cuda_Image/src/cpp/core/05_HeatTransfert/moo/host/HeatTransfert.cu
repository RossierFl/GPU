#include <iostream>
#include <assert.h>

#include "HeatTransfert.h"
#include "Device.h"
#include "MathTools.h"

using std::cout;
using std::endl;

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Imported	 	*|
 \*-------------------------------------*/

extern __global__ void heatTransfert(float* ptrDevImageAInput, float* ptrDevImageBOutput,int w, int h);
extern __global__ void heatEcrasement(float* ptrDevImageInput,float* ptrDevImageHeaters ,float* ptrDevImageOutput,int w,int h);
extern __global__ void heatToScreenImageHSB(float* ptrDevImageInput, uchar4* ptrDevImageGL, int w, int h);

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

HeatTransfert::HeatTransfert(int w, int h,float dt,float k)
    {
    // Inputs
    this->w = w;
    this->h = h;
    this->dt=dt;
    this->k=k;

    // Tools
    this->dg = dim3(8, 8, 1); // disons a optimiser
    this->db = dim3(16, 16, 1); // disons a optimiser
    this->t=0;

    //Outputs
    this->title="[API Image Cuda] : HeatTransfert CUDA";

    // Check:
    //print(dg, db);
    Device::assertDim(dg, db);
    assert(w== h);

    cout << endl<<"[CBI] HeatTransfert dt =" << dt;
    }

HeatTransfert::~HeatTransfert()
    {
    // rien
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
    t+=dt;
    }

/**
 * Override
 */
void HeatTransfert::runGPU(uchar4* ptrDevPixels)
    {

    heatTransfert<<<dg,db>>>(float* ptrDevImageAInput, float* ptrDevImageBOutput,int w, int h);
   heatEcrasement<<<dg,db>>>(float* ptrDevImageInput,float* ptrDevImageHeaters ,float* ptrDevImageOutput,int w,int h);
     heatToScreenImageHSB<<<dg,db>>>(float* ptrDevImageInput, uchar4* ptrDevImageGL, int w, int h);
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
    return  h;
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
 void initGPUMemory(){
	 HANDLE_ERROR(cudaMalloc(&ptrImageDeviceA,SIZE_BAND));
    HANDLE_ERROR(cudaMemset(ptrImageDeviceA,0,SIZE_BAND));
	 HANDLE_ERROR(cudaMalloc(&ptrImageDeviceB,SIZE_BAND));
    HANDLE_ERROR(cudaMemset(ptrImageDeviceB,0,SIZE_BAND));
	 HANDLE_ERROR(cudaMalloc(&prtImageHeats,SIZE_BAND));
    HANDLE_ERROR(cudaMemset(prtImageHeats,0,SIZE_BAND));
 }
 
 void createDataForGPU(){
	uchar4* ptrImageDeviceA;
	uchar4* ptrImageDeviceB;
	uchar4* prtImageHeats;
 }
 
 void initGPUFirstStep(int h,int w,float k){
	heatEcrasement<<<dg,db>>>(ptrImageDeviceA,ptrDevImageHeaters ,ptrImageDeviceB,int w,int h);
	heatTransfert<<<dg,db>>>(ptrImageDeviceA,ptrImageDeviceB,int w, int h);
  
 }
 
 void freeGPUMemory(){
	HANDLE_ERROR(cudaFree(ptrImageDeviceA));
	HANDLE_ERROR(cudaFree(ptrImageDeviceB));
	HANDLE_ERROR(cudaFree(prtImageHeats));
 }

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/


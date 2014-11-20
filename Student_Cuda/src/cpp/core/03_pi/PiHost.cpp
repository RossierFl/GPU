
#include "cudaTools.h"
#include "PiDevice.h"
#include "PiHost.h"
#include <iostream>
#include <limits.h>
/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

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
 void PiHost::MyCalculatePI(){



    const size_t SIZE =1*sizeof(float);
    int nSaucissons=INT_MAX/5;
    int nTabSM=32;
    float* ptrDevResult = NULL;
    float ptrHostResult[SIZE];
    dim3 dg = dim3(16,1,1);
    dim3 db = dim3(32,1,1);
    HANDLE_ERROR(cudaMalloc(&ptrDevResult,SIZE));
    HANDLE_ERROR(cudaMemset(ptrDevResult,0,SIZE));

    PiDevice::runPi(nSaucissons,nTabSM,ptrDevResult,dg,db);//asynchronous
    HANDLE_ERROR(cudaMemcpy(ptrHostResult,ptrDevResult,SIZE,cudaMemcpyDeviceToHost));//barriere implicite de sync
    std::cout<<"PI = " << ptrHostResult[0] <<std::endl;;

}
/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/


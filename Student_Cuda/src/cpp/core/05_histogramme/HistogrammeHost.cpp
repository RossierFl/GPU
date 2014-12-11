
#include "cudaTools.h"
#include "HistogrammeDevice.h"
#include "HistogrammeHost.h"
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



 void HistogrammeHost::MyCalculateHistogramme(){




    const int NBR_ENTREES=10;
    const int NBR_SORTIES=255;
    const size_t SIZE_RESULT =NBR_SORTIES*sizeof(float);
    const size_t SIZE_ENTREES =NBR_ENTREES*sizeof(float);
    //INIT entrees Host
    int tabEntreesHost[NBR_ENTREES];
    //7x1 1X20 2x30
    tabEntreesHost[0]=1;
    tabEntreesHost[1]=20;
    tabEntreesHost[2]=1;
    tabEntreesHost[3]=30;
    tabEntreesHost[4]=1;
    tabEntreesHost[5]=1;
    tabEntreesHost[6]=30;
    tabEntreesHost[7]=1;
    tabEntreesHost[8]=1;
    tabEntreesHost[9]=1;



 //   int nbrVecteurComponents=100;
    int nTabSM=NBR_SORTIES;
    int* ptrDevResult = NULL;
    int* ptrDevEntrees = NULL;

    int  hostResult[NBR_SORTIES];
    dim3 dg = dim3(16,1,1);
    dim3 db = dim3(32,1,1);
    //Réserver GM du GPU pour les entrées et sorties en initialiser les mémoires
    HANDLE_ERROR(cudaMalloc(&ptrDevResult,SIZE_RESULT));
    HANDLE_ERROR(cudaMemset(ptrDevResult,0,SIZE_RESULT));
    HANDLE_ERROR(cudaMalloc(&ptrDevEntrees,SIZE_ENTREES));
    HANDLE_ERROR(cudaMemcpy(ptrDevEntrees,tabEntreesHost,SIZE_ENTREES,cudaMemcpyHostToDevice));//Remplir les entrées

  //  int nEntrees,int  nTabSM,float * ptrDevResult,float * tabEntrees,dim3 dg,dim3 db
    HistogrammeDevice::runHistogramme(NBR_ENTREES,nTabSM,ptrDevResult,ptrDevEntrees,dg,db);//asynchronous
    HANDLE_ERROR(cudaMemcpy(hostResult,ptrDevResult,SIZE_RESULT,cudaMemcpyDeviceToHost));//barriere implicite de sync
    std::cout<<"Histogramme = " << hostResult <<std::endl;;
    for(int i=0;i<NBR_SORTIES;i++){

    std::cout<<"Result comparaison  = "<<std::endl;
    std::cout<< i << " = "<< hostResult[i]<< std::endl;

    }

    HANDLE_ERROR(cudaFree(ptrDevEntrees));
    HANDLE_ERROR(cudaFree(ptrDevResult));



}


/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/


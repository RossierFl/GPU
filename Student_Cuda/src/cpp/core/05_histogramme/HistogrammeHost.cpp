
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



    const size_t SIZE =1*sizeof(double);
    int nbrVecteurComponents=2000;
 //   int nbrVecteurComponents=100;
    int nTabSM=32;
    double* ptrDevResult = NULL;
    double hostResult=0;
    dim3 dg = dim3(16,1,1);
    dim3 db = dim3(32,1,1);
    HANDLE_ERROR(cudaMalloc(&ptrDevResult,SIZE));
    HANDLE_ERROR(cudaMemset(ptrDevResult,0,SIZE));

    HistogrammeDevice::runHistogramme(nbrVecteurComponents,nTabSM,ptrDevResult,dg,db);//asynchronous
    HANDLE_ERROR(cudaMemcpy(&hostResult,ptrDevResult,SIZE,cudaMemcpyDeviceToHost));//barriere implicite de sync
    std::cout<<"Histogramme = " << hostResult <<std::endl;;
    double resultTheorique = ResultatTheorique(nbrVecteurComponents);
    std::cout<<"Result comparaison  = " << resultTheorique <<std::endl;;

}

  double HistogrammeHost::ResultatTheorique(long n){
      n--;
      return (n/(double)2)*(n+1);
 }

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/


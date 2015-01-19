
#include "cudaTools.h"
#include "ProduitScalaireDevice.h"
#include "ProduitScalaireHost.h"
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



 void ProduitScalaireHost::MyCalculateProduitScalaire(){



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

    ProduitScalaireDevice::runProduitScalaire(nbrVecteurComponents,nTabSM,ptrDevResult,dg,db);//asynchronous
    HANDLE_ERROR(cudaMemcpy(&hostResult,ptrDevResult,SIZE,cudaMemcpyDeviceToHost));//barriere implicite de sync
    std::cout<<"ProduitScalaire = " << hostResult <<std::endl;;
    double resultTheorique = ResultatTheorique(nbrVecteurComponents);
    std::cout<<"Result comparaison  = " << resultTheorique <<std::endl;;


}

  double ProduitScalaireHost::ResultatTheorique(long n){
      n--;
      return (n/(double)2)*(n+1);
 }

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/


#include <iostream>
#include <limits.h>
#include "AleaTools.h"
#include "Chronos.h"


using std::cout;
using std::endl;

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Imported	 	*|
 \*-------------------------------------*/
extern void computeHistogram_SM(int* dataImg, int dataLength, int* resultHisto, int lengthHisto);
extern void computeHistogram_GM(int* dataImg, int dataLength, int* resultHisto, int lengthHisto);
extern void computeHistogram_SM_OP(int* dataImg, int dataLength, int* resultHisto, int lengthHisto);
extern void computeHistogram_GM_OP(int* dataImg, int dataLength, int* resultHisto, int lengthHisto);
extern void computeHistogram_ZCM(int* dataImg, int dataLength, int* resultHisto, int lengthHisto);
extern bool checkHistogram_host(int* ptrDevRes,int lenght,int n);
extern bool isHistogramGM_Ok(int n);
extern bool isHistogramZeroCopy_Ok(int n);
#define HISTOGRAM_SIZE 256
void fillAndSwapData_deep(int* ptrHostData, int size);
bool checkHistogram_deep(int* ptrHostData, int size, int n);


/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

bool useHistogramDeeperImpl(void);

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/



/*----------------------------------------------------------------------*\
 |*			Implementation 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

void fillAndSwapData_deep(int* ptrHostData, int size){

    //fill the data
    for(int i=0;i<size;i++)
      {
	ptrHostData[i]=i%HISTOGRAM_SIZE;
      }

    //swap
    AleaTools at;
    for(int i=0;i<size*10;i++)
      {
	  int a = at.uniformeAB(0,size-1);
	  int b = at.uniformeAB(0,size-1);
	  int tmpA = ptrHostData[a];
	  int tmpB = ptrHostData[b];
	  ptrHostData[a]=tmpB;
	  ptrHostData[b] = tmpA;
      }
}

bool checkHistogram_deep(int* ptrHostData, int size, int n){
  int expectedResult = n/size;
  bool isOK = true;
  for(int i=0;i<size;i++)
    {
      if(ptrHostData[i]!=expectedResult){
	  printf("Fail at %d with value %d, expected %d\n",i,ptrHostData[i],expectedResult);
	  isOK =  false;
      }
    }
  return isOK;
}


bool useHistogramDeeperImpl(void)
    {
    Chronos chrono;

    cout << endl << "[Histogram]" << endl;
    chrono.start();
    bool isOk = false;
    int n = 10240000;
    int* ptrHostData = new int[n];
    fillAndSwapData_deep(ptrHostData,n); //create init tab
    int* ptrHostHisto = new int[HISTOGRAM_SIZE];
    chrono.stop();
    chrono.print("Time fill and swap data :");

    //SM part
    /*chrono.start();
    computeHistogram_SM_OP(ptrHostData, n, ptrHostHisto, HISTOGRAM_SIZE);
    chrono.stop();
    chrono.print("Time compute histogram with SM :");

    chrono.start();
    isOk = checkHistogram_deep(ptrHostHisto,HISTOGRAM_SIZE,n);
    if(isOk)printf("Histogram result : SUCCESS \n");
    else printf("Histogram result : FAIL \n");*/

    //GM part
    chrono.start();
    computeHistogram_GM_OP(ptrHostData, n, ptrHostHisto, HISTOGRAM_SIZE);
    chrono.stop();
    chrono.print("Time compute histogram with GM :");

    chrono.start();
    isOk = checkHistogram_deep(ptrHostHisto,HISTOGRAM_SIZE,n);
    if(isOk)printf("Histogram result : SUCCESS \n");
    else printf("Histogram result : FAIL \n");


    chrono.stop();
    chrono.print("Time checking histogram on CPU :");

    //ZCM part
    /*chrono.start();
    computeHistogram_ZCM(ptrHostData, n, ptrHostHisto, HISTOGRAM_SIZE);
    chrono.stop();
    chrono.print("Time compute histogram with ZCM :");

    chrono.start();
    isOk = checkHistogram_deep(ptrHostHisto,HISTOGRAM_SIZE,n);
    if(isOk)printf("Histogram result : SUCCESS \n");
    else printf("Histogram result : FAIL \n");


    chrono.stop();
    chrono.print("Time checking histogram on CPU :");*/


    return true;
    }

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/


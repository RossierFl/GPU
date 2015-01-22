#include <iostream>
#include <limits.h>
#include "Chronos.h"
#include "AleaTools.h"

using std::cout;
using std::endl;

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Imported	 	*|
 \*-------------------------------------*/

extern void HistoOMPSequentiel(int* ptrData, int n, int* ptrResult, int histoSize);
extern void HistoOMPEntrelacerPromotionTab(int* ptrData, int n, int* ptrResult, int histoSize);
extern void HistoOMPEntrelacerCritical(int* ptrData, int n, int* ptrResult, int histoSize);
extern void HistoOMPEntrelacerAtomic(int* ptrData, int n, int* ptrResult, int histoSize);
extern void HistoOMPforCritical(int* ptrData, int n, int* ptrResult, int histoSize);
extern void HistoOMPforAtomic(int* ptrData, int n, int* ptrResult, int histoSize);
extern void HistoOMPforPromotionTab(int* ptrData, int n, int* ptrResult, int histoSize);
extern void HistoOMPforReduction(int* ptrData, int n, int* ptrResult, int histoSize);
#define HISTOGRAM_SIZE 256
void fillAndSwapData_deep(int* ptrHostData, int size);
bool checkHistogram_deep(int* ptrHostData, int size, int n);
void initTabResult(int* ptrResult, int size);
/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

bool useHisto(void);

typedef void (*implementation)(int* ptrData, int n, int* ptrResult, int histoSize);


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
	  printf("Fail at %d with value %d, expected %d \n",i,ptrHostData[i],expectedResult);
	  isOK = false;
      }
    }
  return isOK;
}

void initTabResult(int* ptrResult, int size){
  for(int i=0;i<size;i++)
    {
      ptrResult[i]=0;
    }
}

bool useHisto(void)
    {
    cout << endl << "[Histogram OMP ]" << endl;

    int n = 10240000;
    implementation impl[8];
    impl[0] = HistoOMPSequentiel;
    impl[1] = HistoOMPEntrelacerPromotionTab;
    impl[2] = HistoOMPEntrelacerCritical;
    impl[3] = HistoOMPEntrelacerAtomic;
    impl[4] = HistoOMPforCritical;
    impl[5] = HistoOMPforAtomic;
    impl[6] = HistoOMPforPromotionTab;
    impl[7] = HistoOMPforReduction;
    std::string implName[8];
    implName[0] = "HistoOMPSequentiel";
    implName[1] = "HistoOMPEntrelacerPromotionTab";
    implName[2] = "HistoOMPEntrelacerCritical";
    implName[3] = "HistoOMPEntrelacerAtomic";
    implName[4] = "HistoOMPforCritical";
    implName[5] = "HistoOMPforAtomic";
    implName[6] = "HistoOMPforPromotionTab";
    implName[7] = "HistoOMPforReduction";
    int* ptrHostData = new int[n];
    fillAndSwapData_deep(ptrHostData,n); //create init tab
    int* ptrHostHisto = new int[HISTOGRAM_SIZE];
    initTabResult(ptrHostHisto,HISTOGRAM_SIZE);
    Chronos chrono;
    bool isOK = false;
    for(int i=0;i<8;i++)
      {
	  cout << endl << "[Histogram OMP Impl: "<<implName[i]<<"]" << endl;
	  chrono.start();
	  impl[i](ptrHostData,n,ptrHostHisto,HISTOGRAM_SIZE);
	  chrono.stop();
	  chrono.print("Time for CPU : ");
	  isOK = checkHistogram_deep(ptrHostHisto,HISTOGRAM_SIZE,n);
	  //ptrHostHisto= new int[HISTOGRAM_SIZE];
	  initTabResult(ptrHostHisto,HISTOGRAM_SIZE);
	  if(!isOK){
	      break;
	  }
      }

    return isOK;
    }

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/


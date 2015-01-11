#include "Indice2D.h"
#include "IndiceTools.h"
#include "DomaineMath.h"
#include "cudaTools.h"
#include "Device.h"
#include "HeatTransfertMath.h"
#include "CalibreurCudas.h"
#include "ColorTools_GPU.h"
#include <stdio.h>


/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Imported	 	*|
 \*-------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

__global__ void heatTransfertDiffusion(float* ptrDevImageA,float* ptrDevImageB, bool isImageAInput, int w, int h,float k);
__global__ void heatTransfertEcrasement(float* ptrDevInputHeater, float* ptrDevInputImage,float* ptrDevOutput, int w, int h);
__global__ void heatTransfertConvertData(CalibreurCudas calibreurCuda,float* ptrDevInput, uchar4* ptrDevImage, int w, int h);



/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/



/*----------------------------------------------------------------------*\
 |*			Implementation 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

__global__ void heatTransfertDiffusion(float* ptrDevImageA,float* ptrDevImageB, bool isImageAInput, int w, int h, float k){
      HeatTransfertMath* heatTransfertMath = new HeatTransfertMath(k);
      /*if(!isImageAInput){//switch it here to avoid another if later, all thread should do the same here
	  float* tmp = ptrDevImageB;
	  ptrDevImageB = ptrDevImageA;
	  ptrDevImageA = tmp;
      }*/
      const int TID = Indice2D::tid();
      const int NB_THREAD = Indice2D::nbThread();

      const int WH=w*h;


      int pixelI;
      int pixelJ;

      int s = TID;
      while (s < WH)
  	{
	  IndiceTools::toIJ(s, w, &pixelI, &pixelJ); // update (pixelI, pixelJ)
	  if(pixelI!=0&&pixelI!=h&&pixelJ!=0&&pixelJ!=w){//not on the side of the image
		  if(!isImageAInput)heatTransfertMath->getNewPixelValue(&ptrDevImageB[s],ptrDevImageA,k,s,w); // update color
		  else heatTransfertMath->getNewPixelValue(&ptrDevImageA[s],ptrDevImageB,k,s,w); // update color
		  //ptrDevImageB[s] = newPixelValue;
	  }
	  s += NB_THREAD;
  	}
      delete heatTransfertMath;
}
__global__ void heatTransfertEcrasement(float* ptrDevInputHeater, float* ptrDevInputImage,float* ptrDevOutput, int w, int h){

      const int TID = Indice2D::tid();
      //if(TID==0)printf("start heatTransfertEcrasement\n");
      const int NB_THREAD = Indice2D::nbThread();

      const int WH=w*h;


      //int pixelI;
      //int pixelJ;

      int s = TID;
      while (s < WH)
      {
	  //IndiceTools::toIJ(s, w, &pixelI, &pixelJ); // update (pixelI, pixelJ)

	  // (i,j) domaine ecran
	  //float* pixelValue = 0.0;
	  ptrDevOutput[s] = ptrDevInputImage[s];
	  if(ptrDevInputHeater[s]!=0.0){//ok an if, but most of the image will be copied
	      ptrDevOutput[s]=ptrDevInputHeater[s];
	  }
	  s += NB_THREAD;
      }
      //if(TID==0)printf("end heatTransfertEcrasement\n");
}
__global__ void heatTransfertConvertData(CalibreurCudas calibreurCuda, float* ptrDevInput, uchar4* ptrDevImage, int w, int h){
	const int TID = Indice2D::tid();
        const int NB_THREAD = Indice2D::nbThread();

        const int WH=w*h;


        //int pixelI;
        //int pixelJ;

        int s = TID;
        while (s < WH)
        {
  	  //IndiceTools::toIJ(s, w, &pixelI, &pixelJ); // update (pixelI, pixelJ)

  	  // (i,j) domaine ecran
  	  //float* pixelValue = 0.0;
            float hue = calibreurCuda.calibrate(ptrDevInput[s]);
            ColorTools::HSB_TO_RVB(hue, &ptrDevImage[s]);
            s += NB_THREAD;
        }
}
/*__global__ void fractaleNewton(uchar4* ptrDevPixels, int w, int h, DomaineMath domaineMath, int n, float t,
	float epsilonx, float epsilonf, float epsilonxstar,float* jacobiMatrix)
    {
    NewtonMath* newtonMath = new NewtonMath(n);

    const int TID = Indice2D::tid();
    const int NB_THREAD = Indice2D::nbThread();

    const int WH=w*h;

    uchar4 color;

    double x;
    double y;

    int pixelI;
    int pixelJ;

    int s = TID;
    while (s < WH)
	{
	IndiceTools::toIJ(s, w, &pixelI, &pixelJ); // update (pixelI, pixelJ)

	// (i,j) domaine ecran
	// (x,y) domaine math
	domaineMath.toXY(pixelI, pixelJ, &x, &y); //  (i,j) -> (x,y)

	newtonMath->colorXY(&color,x, y,t,epsilonx,epsilonf,epsilonxstar,jacobiMatrix); // update color

	ptrDevPixels[s] = color;

	s += NB_THREAD;
	}
    delete newtonMath;

    }*/

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/


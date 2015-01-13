#include "Indice2D.h"
#include "IndiceTools.h"
#include "DomaineMath.h"
#include "cudaTools.h"
#include "Device.h"
#include "HeatTransfertMath.h"
#include "CalibreurCuda.h"
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

__global__ void diffusion(float* ptrDevImageA,float* ptrDevImageB, int w, int h, float k, bool imgAIsInput);
__global__ void ecrasement(float* ptrDevInputHeater, float* ptrDevInputImage,float* ptrDevOutput, int w, int h);
__global__ void toScreenImageHSB(CalibreurCuda calibreurCuda,float* ptrDevInput, uchar4* ptrDevImage, int w, int h);



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

__global__ void diffusion(float* ptrDevImageA,float* ptrDevImageB, int w, int h, float k, bool imgAIsInput){
      HeatTransfertMath* math = new HeatTransfertMath(k);

      const int TID = Indice2D::tid();
      const int NB_THREAD = Indice2D::nbThread();

      const int WH=w*h;

      int pixelI;
      int pixelJ;

      int s = TID;
      while (s < WH)
  	{
	  IndiceTools::toIJ(s, w, &pixelI, &pixelJ);
	  // 1 pixel band around image not calc to avoid 9 branch
	  if(pixelI !=0 && pixelI != h && pixelJ != 0 && pixelJ != w){
		  if(!imgAIsInput)
		      math->updateHeat(&ptrDevImageB[s],ptrDevImageA,k,s,w); // update color
		  else
		      math->updateHeat(&ptrDevImageA[s],ptrDevImageB,k,s,w); // update color
	  }
	  s += NB_THREAD;
  	}
      delete math;
}
__global__ void ecrasement(float* ptrDevInputHeater, float* ptrDevInputImage,float* ptrDevOutput, int w, int h){

      const int TID = Indice2D::tid();

      const int NB_THREAD = Indice2D::nbThread();

      const int WH=w*h;

      int s = TID;
      while (s < WH)
      {
	  ptrDevOutput[s] = ptrDevInputImage[s];
	  if(ptrDevInputHeater[s]!=0.0){
	      ptrDevOutput[s]=ptrDevInputHeater[s];
	  }
	  s += NB_THREAD;
      }
}
__global__ void toScreenImageHSB(CalibreurCuda calibreurCuda, float* ptrDevInput, uchar4* ptrDevImage, int w, int h){
	const int TID = Indice2D::tid();
        const int NB_THREAD = Indice2D::nbThread();

        const int WH=w*h;

        int s = TID;
        while (s < WH)
        {
            float hue = calibreurCuda.calibrer(ptrDevInput[s]);
            ColorTools::HSB_TO_RVB(hue, &ptrDevImage[s]);
            s += NB_THREAD;
        }
}

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/


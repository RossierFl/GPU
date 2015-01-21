

#include "ConvolutionMOO.h"
#include "ConvolutionMath.h"

#include <omp.h>
#include "IndiceTools.h"
#include "OmpTools.h"


/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

/*--------------------------------------*\
 |*		Private
 \*-------------------------------------*/

/*----------------------------------------------------------------------*\
 |*			Implementation 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

ConvolutionMOO::ConvolutionMOO(unsigned int w, unsigned int h, float dt)
    {
    this->w = 640;
    this->h = 360;
    this->k = 9;

    // Tools

    this->t = 0;

    //Outputs
    this->title = "[API Image Cuda] : Convolution CUDA";
   // this->videoPath = "/media/Data/Video/nasaFHD_short.avi";
   // this->videoTitle = "NASA FHD SHORT";

    this->videoPath = "/media/Data/Video/neilPryde.avi";
    this->videoTitle = "neilPryde";

    //size_t sizeOctets = w * h * sizeof(uchar4);
    ptrHostMemory = new uchar4[w*h];
    //HANDLE_ERROR(cudaHostAlloc((void**) &(this->ptrHostMemory), sizeOctets, cudaHostAllocDefault));

    this->captureur = new CaptureVideo(videoPath, videoTitle, this->ptrHostMemory);

    const int N = k * k;

 //   HANDLE_ERROR(cudaHostAlloc((void**) &(this->ptrHostNoyau), N * sizeof(float), cudaHostAllocDefault));
    ptrHostNoyau = new float[N];

    fillDetourage (ptrHostNoyau);

   // HANDLE_ERROR(cudaMalloc((void **) &ptrDeviceNoyau, N * sizeof(float)));
   // HANDLE_ERROR(cudaMemcpy(ptrDeviceNoyau, ptrHostNoyau, N * sizeof(float), cudaMemcpyHostToDevice));

   /* sizeSM = 2 * db.x * sizeof(uchar);
    sizeResult = 2 * dg.x * sizeof(uchar);
    ptrHostResult = (uchar*) malloc(sizeResult);*/
    ptrHostResult = new uchar[2];

    // first contains min of each block, then max of each block
  //  HANDLE_ERROR(cudaMalloc((void**) &ptrDevResult, sizeResult));
    }

ConvolutionMOO::~ConvolutionMOO(void)
    {
    // rien
    delete[] ptrHostMemory;
    delete[] ptrHostNoyau;
    delete[] ptrHostResult;
    delete convolutionDevice;
    }

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

void ConvolutionMOO::process(uchar4* ptrTabPixels, int w2, int h2)
    {
    /*   if (isEntrelacement)
     {
     entrelacementOMP(ptrTabPixels,w,h); // Plus lent
     }
     else
     {
     forAutoOMP(ptrTabPixels,w,h);  // Plus rapide
     }

     isEntrelacement=!isEntrelacement;// Pour tester que les deux implementations fonctionnent*/





       Mat matImage = captureur->capturer();

       uchar4* image = CaptureVideo::castToUChar4(&matImage);
       size_t size_image = w*h*sizeof(uchar4);

       memcpy ( ptrTabPixels,image,size_image);

       convolutionDevice->colorToGreyTexture(ptrTabPixels,w,h);

       convolutionDevice->convolutionTextureKernel(ptrTabPixels,ptrHostNoyau,k,w,h,t);

       convolutionDevice->findMinMaxTexture(ptrTabPixels,ptrHostResult,w,h);

       uchar max = ptrHostResult[1];
       uchar min = ptrHostResult[0];

       // affine transformation
       float a = 255.0f/(float)(max-min);
       float b = 0;
       if(min != 0)
   	b = 255.0f/((-max/(float)min)+1.0f);
       convolutionDevice->affineTransformTexture(ptrTabPixels, a, b, w, h,0);
       //cudaUnbindTexture(textureRef);

    }

void ConvolutionMOO::animationStep()
    {
    t += dt;
    }

/*--------------*\
 |*	get	*|
 \*-------------*/

float ConvolutionMOO::getT()
    {
    return t;
    }

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/
/**
 * Noyau detourage 9x9
 */
void ConvolutionMOO::fillDetourage(float* ptrNoyau)
    {
    const int N = 9*9;
    // Tab auto temporaire
    float tab[N] =
	    {
		    0.0828, 0.1987, 0.3705, 0.5366, 0.6063, 0.5366, 0.3705, 0.1987, 0.0828, 0.1987, 0.4746, 0.8646, 1.1794, 1.2765, 1.1794, 0.8646, 0.4746, 0.1987, 0.3705, 0.8646, 1.3475, 1.0033, 0.4061, 1.0033, 1.3475, 0.8646, 0.3705, 0.5366, 1.1794, 1.0033, -2.8306, -6.4829, -2.8306, 1.0033, 1.1794, 0.5366, 0.6063, 1.2765, 0.4061, -6.4829, -12.7462, -6.4829, 0.4061, 1.2765, 0.6063, 0.5366, 1.1794, 1.0033, -2.8306, -6.4829, -2.8306, 1.0033, 1.1794, 0.5366, 0.3705, 0.8646, 1.3475, 1.0033, 0.4061, 1.0033, 1.3475, 0.8646, 0.3705, 0.1987, 0.4746, 0.8646, 1.1794, 1.2765, 1.1794, 0.8646, 0.4746, 0.1987, 0.0828, 0.1987, 0.3705, 0.5366, 0.6063, 0.5366, 0.3705, 0.1987, 0.0828
	    };

    for (int i = 1; i <= N; i++)
	{
	ptrNoyau[i - 1] = tab[i - 1] / 100.0f;
	}
    }


/*void ConvolutionMOO::entrelacementOMP(uchar4* ptrTabPixels,int w, int h)
 {
 ConvolutionMath convolutionMath(w,h);


 const int WH = w * h;


 #pragma omp parallel
 {
 const int NB_THREAD = OmpTools::getNbThread();// dans region parallel
 const int TID = OmpTools::getTid();
 int s = TID; // in [0,...

 int i;
 int j;
 while (s < WH)
 {
 IndiceTools::toIJ(s, w, &i, &j); // s[0,W*H[ --> i[0,H[ j[0,W[

 convolutionMath.colorIJ(&ptrTabPixels[s], i, j,t);

 s += NB_THREAD;
 }
 }
 }*/

/**
 * Code naturel et direct OMP
 */
/*void ConvolutionMOO::forAutoOMP(uchar4* ptrTabPixels,int w,int h)
 {
 // TODO
 ConvolutionMath convolutionMath(w,h); // ici pour preparer cuda
 #pragma omp paralllel for
 for (int i=0;i<h ;i++){

 for (int j=0;j< w;j++){

 int s = IndiceTools::toS(w, i, j);    // i[0,H[ j[0,W[  --> s[0,W*H[
 convolutionMath.colorIJ(ptrTabPixels,  i,  j,  t);
 // vagueMath.colorIJ(&ptrTabPixels[s], i, j,t);
 }
 }
 }
 */
/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/

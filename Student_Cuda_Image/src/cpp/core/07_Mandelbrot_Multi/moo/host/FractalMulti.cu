#include <assert.h>

#include "FractalMulti.h"
#include "Device.h"
#include "MathTools.h"
#include <omp.h>

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Imported	 	*|
 \*-------------------------------------*/

__global__ void fractalMulti(uchar4* ptrDevPixels, int w, int h,bool julia, DomaineMath domaineMath, int n,float t,double cx, double cy, int imgOffset);
//uchar4* ptrDevPixels,int w, int h,bool julia,DomaineMath domaineMath, int n,double cx, double cy

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

FractalMulti::FractalMulti(int w, int h, int dt,  int nMin,int nMax,bool julia,double cx,double cy,double xMin, double xMax, double yMin, double yMax) :
	variateurAnimation(IntervalI(nMin,nMax), dt)
    {
    // Inputs
    this->first = true;
    this->w = w;
    this->h = h;
    this->julia = julia;
    this->cx = cx;
    this->cy = cy;
    this->n = nMin;
    this->t=0;
    // Tools
    this->dg = dim3(8, 8, 1); // disons a optimiser
    this->db = dim3(16, 16, 1); // disons a optimiser
    Device::assertDim(dg, db);
    ptrDomaineMathInit=new DomaineMath(xMin,yMin,xMax,yMax);

    //Outputs
    this->title = "[API Image Fonctionelle] : Fractal zoomable CUDA MULTIGPU Rossier";
    this->nbGPU = 6;
    this->heightBande = h/nbGPU;
    //memory management for 5 GPU
    this->sizeBande=this->heightBande*w*sizeof(uchar4);
    this->bandeI = new uchar4*[5];

    for(int i=0;i<nbGPU-1;i++)
      {
	cudaSetDevice(i);
	//uchar4* ptrDevBande;
	//bandeI[i] = ptrDevBande;
	HANDLE_ERROR(cudaMalloc((void**) &bandeI[i], sizeBande)); // Device memory allocation (*)
	HANDLE_ERROR(cudaMemset(bandeI[i],0,sizeBande)) ;
      }
    cudaSetDevice(5);
    // Check:
    //print(dg, db);
    std::cout<<"construc"<<std::endl;
    }

FractalMulti::~FractalMulti()
    {
   delete ptrDomaineMathInit;
    }

/*-------------------------*\
 |*	Methode		    *|
 \*-------------------------*/

/**
 * Override
 */
void FractalMulti::animationStep()
    {
    this->t = variateurAnimation.varierAndGet(); // in [0,2pi]
    }

/**
 * Override
 */
void FractalMulti::runGPU(uchar4* ptrDevPixels, const DomaineMath& domaineMath)
{

   //could be more generic
  assert(h%nbGPU==0);//


  omp_set_num_threads(nbGPU);
/*#pragma omp parallel
	{*/
#pragma omp parralel for
  for(int i=0;i<nbGPU;i++)
    {
     // if(!this->first){
	  cudaSetDevice(i);
      /*}else{
	  this->first = false;
      }*/

      int offset = w*h/nbGPU;
      int imgOffset = (h/6)*i;
      if(i==5){
	  fractalMulti<<<dg,db>>>(ptrDevPixels+offset*i,w,this->heightBande,julia,domaineMath,n,t,cx,cy,imgOffset);
	  Device::synchronize();

      }else{

	  uchar4* ptrDevBandeInitialGPU = ptrDevPixels+offset*i;
	  fractalMulti<<<dg,db>>>(bandeI[i],w,this->heightBande,julia,domaineMath,n,t,cx,cy,imgOffset);
	  HANDLE_ERROR(cudaMemcpy(ptrDevBandeInitialGPU,  bandeI[i], sizeBande, cudaMemcpyDeviceToDevice));// Device -> Host
      }
      Device::checkKernelError("fractalMulti");
      //HANDLE_ERROR(cudaFree(ptrDevRes)); // device dispose memory in (*)
    }

  /*for(int i=0;i<nbGPU;i++)
    {
      HANDLE_ERROR(cudaMemset(bandeI[i],0,sizeBande)) ;
    }*/
	  /*const int TID = omp_get_thread_num();
	  if(TID==0){
	      cudaSetDevice(0);

	  }else{
	      cudaSetDevice(TID);
	      //fractalMulti<<<dg,db>>>(ptrDevPixels+,w,heightPerGPU,julia,domaineMath,n,t,cx,cy);
	  }*/
	//}

    Device::synchronize();
    Device::checkKernelError("fractalMulti");

    //uchar4* ptrDevPixels,int w, int h,bool julia,DomaineMath domaineMath, int n,double cx, double cy
    }

/*--------------*\
 |*	get	 *|
 \*--------------*/

/**
 * Override
 */
DomaineMath* FractalMulti::getDomaineMathInit(void)
    {
    return ptrDomaineMathInit;
    }

/**
 * Override
 */
float FractalMulti::getT(void)
    {
    return t;
    }

/**
 * Override
 */
int FractalMulti::getW(void)
    {
    return w;
    }

/**
 * Override
 */
int FractalMulti::getH(void)
    {
    return h;
    }

/**
 * Override
 */
string FractalMulti::getTitle(void)
    {
    return title;
    }

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/


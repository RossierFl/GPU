#include <assert.h>

#include "RayTracing.h"
#include "Device.h"
#include "MathTools.h"
#include <stdio.h>

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Imported	 	*|
 \*-------------------------------------*/

__global__ void rayTracingGPU(uchar4* ptrDevPixels, int w, int h, float t, Sphere* spheres, int n);

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

RayTracing::RayTracing(int w, int h, float dt, double x1, double y1, double x2, double y2,double z1,double z2 ,double rayonMax,int nbrBalls) :
		variateurAnimation(IntervalF(0,10), dt)
    {
    // Inputs
    this->w = w;
    this->h = h;
	

      spheres= new Sphere[nbrBalls];
      std::cout<<"NBR BALLLS"<<nbrBalls<<std::endl;
      for(int i = 0;i<nbrBalls;i++)
      {
  	    float x = drand48();
  	    float y = drand48();
  	    float z = drand48();
  	    float3 centre;
  	    centre.x = x1+x*(x2-x1);
  	    centre.y = y1+y*(y2-y1);
  	    centre.z = z1+z*(z2-z1);
  	    float r = drand48();
  	    float hue = drand48();
  	    spheres[i] = Sphere(centre, 20+r*rayonMax, hue);
      }
      for(int i =0;i<nbrBalls;i++){
	  //std::cout<<spheres[i].hue(2)<<std::endl;
      }
    this->nbrBalls = nbrBalls;
	
    // Tools
    this->dg = dim3(8, 8, 1); // disons a optimiser
    this->db = dim3(16, 16, 1); // disons a optimiser
    this->t = variateurAnimation.varierAndGet();
    InitSphereMemory();

    //Outputs
    this->title = "[API Image Normale] : RayTracing non-zoomable CUDA";

    // Check:
    //print(dg, db);
    Device::assertDim(dg, db);
    assert(w == h);
    }



RayTracing::~RayTracing()
    {
    cudaFree(ptrSpheresDev);//free mat
    delete spheres;
    }

/*-------------------------*\
 |*	Methode		    *|
 \*-------------------------*/

/**
 * Override
 */
void RayTracing::animationStep()
    {
    this->t = variateurAnimation.varierAndGet();
    }

/**
 * Override
 */
void RayTracing::runGPU(uchar4* ptrDevPixels)
    {

    rayTracingGPU<<<dg,db>>>(ptrDevPixels,w,h,t,ptrSpheresDev,nbrBalls);//call

    cudaDeviceSynchronize();

    }

/*--------------*\
 |*	get	 *|
 \*--------------*/

/**
 * Override
 */
float RayTracing::getT(void)
    {
    return t;
    }

/**
 * Override
 */
int RayTracing::getW(void)
    {
    return w;
    }

/**
 * Override
 */
int RayTracing::getH(void)
    {
    return h;
    }

/**
 * Override
 */
string RayTracing::getTitle(void)
    {
    return title;
    }

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

void RayTracing::InitSphereMemory(){

        HANDLE_ERROR(cudaMalloc(&ptrSpheresDev,nbrBalls*sizeof(Sphere)));//malloc all spheres
        HANDLE_ERROR(cudaMemcpy(ptrSpheresDev,spheres,nbrBalls*sizeof(Sphere),cudaMemcpyHostToDevice));//fill with spheres

}

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/

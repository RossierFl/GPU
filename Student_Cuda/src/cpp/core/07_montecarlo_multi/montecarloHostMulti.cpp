#include <iostream>
#include <limits.h>
#include "montecarloDeviceMulti.h"
#include "montecarloHostMulti.h"
#include "cudaTools.h"
#include "Device.h"
#include <assert.h>
#include <omp.h>

#include <curand_kernel.h>


using std::cout;
using std::endl;

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Imported	 	*|
 \*-------------------------------------*/

extern bool isMontecarlo_Ok(long n, float xMin, float xMax, int m);

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

bool useMontecarlo(void);

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/



/*----------------------------------------------------------------------*\
 |*			Implementation 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/



bool MontecarloHostMulti::myCalculateMontecarloMulti(void)
    {
    cout << endl << "[Montecarlo]" << endl;

    bool isOk = true;

    long n = 6000000;
    float xMin = 0.0;
    float xMax = 2.0;
    int m = 1;

    //isOk&= isMontecarlo_Ok(n, xMin, xMax, m);


    //printf("Montecarlo[n=%l, min=%f, max=%f, m=%d]\n", n, xMin, xMax, m);
    std::cout<<"Montecarlo start datat n : "<<n<<" min : "<< xMin << " max : "<< xMax << " m : "<< m << std::endl;

    float* resultHost = new float[6];
    	assert(n%6==0);//could be more generic
    	int nbNPerGPU = n/6;
    	int nThreadPerBlock = 4;
    	dim3 dg(1, 1, 1); // TODO to optimize
    	dim3 db(nThreadPerBlock, 1, 1); // TODO to optimize
    	Device::checkDimError(dg, db);
    	Device::checkDimOptimiser(dg, db);

    	Device::checkKernelError("setup_kernel_rand_montecarloMulti");
    	int nbGPU = 6; //could be more generic
    	omp_set_num_threads(nbGPU);
    #pragma omp parralel for
    	for(int i=0;i<nbGPU;i++)
    	  {
    	    cudaSetDevice(i);
    	   // printf("i:%d\n",i);

    	    //init random generator
    	    curandState* ptrDevRandom;
    	    size_t sizeRandom = sizeof(curandState) * nThreadPerBlock;
    	    HANDLE_ERROR(cudaMalloc((void**) &ptrDevRandom, sizeRandom));
    	    HANDLE_ERROR(cudaMemset(ptrDevRandom, 0, sizeRandom));

    	    float* ptrDevGM = NULL;
    	    size_t size = sizeof(float);
    	    size_t sizeTabSM = sizeof(float) * nThreadPerBlock;
    	    HANDLE_ERROR(cudaMalloc(&ptrDevGM, size));
    	    HANDLE_ERROR(cudaMemset(ptrDevGM, 0, size));




    	    // Récupération du résultat
    	MontecarloDeviceMulti montDevice =  MontecarloDeviceMulti();
    	    	montDevice.runMontecarloMulti(ptrDevRandom,ptrDevGM,  xMin, xMax, m, n, sizeTabSM, dg, db);
    	    HANDLE_ERROR(cudaMemcpy(&resultHost[i], ptrDevGM, size, cudaMemcpyDeviceToHost)); // barrière de synchronisation
    	  }
    	float result = 0.0;
    	for(int i=0;i<nbGPU;i++)//could be more generic
    	  {
    	      result += resultHost[i];
    	  }
    	result /= nbGPU;


    	// Affichage du résultat
    	printf("MontecarloMulti[n=%d, min=%f, max=%f, m=%d] = %f\n", n, xMin, xMax, m, result);

    	return true;




    }

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/


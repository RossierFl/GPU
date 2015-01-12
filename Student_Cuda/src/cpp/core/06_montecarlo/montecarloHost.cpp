#include <iostream>
#include <limits.h>
#include "montecarloDevice.h"
#include "montecarloHost.h"
#include "cudaTools.h"

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



bool MontecarloHost::myCalculateMontecarlo(void)
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
    	float resultHost = 0;
    	float* ptrDevGM = NULL;
    	size_t size = sizeof(float);
    	int nThreadPerBlock = 4;
    	size_t sizeTabSM = sizeof(float) * nThreadPerBlock;
    	HANDLE_ERROR(cudaMalloc(&ptrDevGM, size));
    	HANDLE_ERROR(cudaMemset(ptrDevGM, 0, size));

    	dim3 dg(1, 1, 1); // TODO to optimize
    	dim3 db(nThreadPerBlock, 1, 1); // TODO to optimize
    //	Device::checkDimError(dg, db);
    	//Device::checkDimOptimiser(dg, db);

    	//init random generator
    	curandState* ptrDevRandom;
    	size_t sizeRandom = sizeof(curandState) * nThreadPerBlock;
    	HANDLE_ERROR(cudaMalloc((void**) &ptrDevRandom, sizeRandom));
    	HANDLE_ERROR(cudaMemset(ptrDevRandom, 0, sizeRandom));

    	//Ajouter une fonction
    	MontecarloDevice montDevice =  MontecarloDevice();
    	montDevice.runMontecarlo(ptrDevRandom,ptrDevGM,  xMin, xMax, m, n, sizeTabSM, dg, db);
    	// Récupération du résultat
    	HANDLE_ERROR(cudaMemcpy(&resultHost, ptrDevGM, size, cudaMemcpyDeviceToHost)); // barrière de synchronisation

    	// Affichage du résultat
    	printf("Montecarlo[n=%d, min=%f, max=%f, m=%d] = %f\n", n, xMin, xMax, m, resultHost);

    return true;
    }

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/


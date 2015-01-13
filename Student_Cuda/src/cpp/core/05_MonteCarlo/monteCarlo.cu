#include <assert.h>
#include <cstdio>
#include <curand_kernel.h>

#include "cuda_utils.h"
#include "cudaTools.h"
#include "Device.h"
#include "Indice1D.h"

using std::cout;
using std::endl;

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

__host__ bool isMonteCarlo_Ok(long n, float xMin, float xMax, int m);

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

__host__ static float computeMonteCarlo(int n);
__global__ static void computeMonteCarloGPU(float* ptrDevGM, int nTabSM, float xMin, float xMax,
	int m, long n, curandState* ptrDevRandom);
__device__ static void reduceIntraThreadMonteCarlo(float* tabSM, float xMin, float xMax, int m, long n,
	curandState* generator);
__device__ static float uniform( float min, float max, curandState &localState);
__global__ static void setup_kernel_rand(curandState* tabGeneratorThread,int deviceId);

/*----------------------------------------------------------------------*\
 |*			Implementation 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

__host__ bool isMonteCarlo_Ok(long n, float xMin, float xMax, int m)
    {
    float resultHost = 0;
    float* ptrDevResult = NULL;
    size_t size = sizeof(float);
    const int nbThreadBlock = 16;
    size_t sizeSM = sizeof(float) * nbThreadBlock;

    HANDLE_ERROR(cudaMalloc(&ptrDevResult, size));
    HANDLE_ERROR(cudaMemset(ptrDevResult, 0, size));

    dim3 dg(1, 1, 1);
    dim3 db(nbThreadBlock, 1, 1);

    //init random generator
    curandState* ptrDevRandomGen;
    size_t sizeRandom = sizeof(curandState) * nbThreadBlock;
    HANDLE_ERROR(cudaMalloc((void**) &ptrDevRandomGen, sizeRandom));
    HANDLE_ERROR(cudaMemset(ptrDevRandomGen, 0, sizeRandom));

    setup_kernel_rand<<<dg,db>>>(ptrDevRandomGen,Device::getDeviceId());

    //Device::checkKernelError("setup_kernel_rand");

    // carefull using int not size_t
    computeMonteCarloGPU<<<dg,db,sizeSM>>>(ptrDevResult, nbThreadBlock, xMin, xMax, m, n, ptrDevRandomGen);

    //Device::checkKernelError("computeMonteCarloGPU");

    HANDLE_ERROR(cudaMemcpy(&resultHost, ptrDevResult, size, cudaMemcpyDeviceToHost));
    // no need of cudaDevice because cudaMemcpy

    printf("Montecarlo[n: %ld, min: %f, max: %f, m: %d] : %f\n", n, xMin, xMax, m, resultHost);
    return true;
    }

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

__host__ float computeMonteCarlo(int n)
    {
	return 0.0;
    }

__global__ void computeMonteCarloGPU(float* ptrDevResult, int sizeTabSM, float xMin, float xMax,
	int m, long n, curandState* ptrDevRandom)
    {
    extern __shared__ float tabSM[];// 1 instance per block !
    const int TID = Indice1D::tid();
    CUDAUtils::initialize(tabSM, sizeTabSM);
    __syncthreads();
    reduceIntraThreadMonteCarlo(tabSM, xMin, xMax, m, n, ptrDevRandom);
    __syncthreads();
    CUDAUtils::reduceIntraBlock(tabSM);
    __syncthreads();
    CUDAUtils::reduceInterBlock(tabSM,ptrDevResult);
    if(TID == 0)
	*ptrDevResult = *ptrDevResult / n * (xMax - xMin) * m;
    }

__device__ float uniform(const float MIN, const float MAX, curandState& localState)
    {
    float r = curand_uniform(&localState);
    return MIN + r * (MAX - MIN);
    }

__device__ void reduceIntraThreadMonteCarlo(float* tabSM, float xMin, float xMax, int m, long n,
	curandState* generator)
    {
    const int TID = Indice1D::tid();
    const int TID_LOCAL = Indice1D::tidLocal();
    const int NB_THREAD = Indice1D::nbThread();
    const float probability = 0.3;
    curandState state = generator[TID];
    float intraThreadSum = 0;
    int s = TID;
    while (s < n)
	{
	float xAlea = uniform(xMin, xMax, state);
	float yAlea = uniform(0, m, state);
	if (yAlea < probability)
	    intraThreadSum++;
	s += NB_THREAD;
	}
    tabSM[TID_LOCAL] = intraThreadSum;
    }

//Nvidia Doc : Each thread gets same seed , a different sequence number , no offset
__global__ void setup_kernel_rand(curandState* tabGeneratorThread,int deviceId)
    {
    int tid = Indice1D::tid();
    //Customisation du generator: Proposition (au lecteur de faire mieux)
    // Contrainte : Doit etre différent d'un GPU à l'autre
    int deltaSeed=deviceId* INT_MAX;
    int deltaSequence=deviceId *100;
    int deltaOffset=deviceId *100;
    int seed=1234+deltaSeed;
    int sequenceNumber=tid+deltaSequence;
    int offset=deltaOffset;
    curand_init(seed, sequenceNumber, offset, &tabGeneratorThread[tid]);
    }



/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/


#include <iostream>
#include <cstdio>
#include <assert.h>

#include "ConvolutionMultiGPU.h"
//#include "ConvolutionMathMultiGPU.h"
#include "Indice2D.h"
#include "IndiceTools.h"
#include "Device.h"
#include "MathTools.h"
#include "Chronos.h"

using std::cout;
using std::endl;

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Imported	 	*|
 \*-------------------------------------*/

//extern __global__ void convolutionKernelMultiGPU(texture<uchar4,2> tex, uchar4* ptrDevPixels, float* ptrDeviceNoyau, int k, int w, int h, float t);
extern __global__ void colorToGreyMultiGPU(uchar4* ptrDevPixels, int w, int h);
extern __global__ void findMinMaxMultiGPU(uchar4* ptrDevPixels, uchar* ptrDevResult,int w, int h);
extern __global__ void affineTransformMultiGPU(uchar4* ptrDevPixels, float a, float b, int w, int h, int offset);

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

texture<uchar4, 2> textureRef;

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

/*----------------------------------------------------------------------*\
 |*			Implementation 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

__device__
void colorIJMultiGPU(uchar4* ptrColor, float* ptrDeviceNoyau, int k, int i, int j, int s)
    {

    float sum = 0.0f;
    int ss = (int)(k*((float)k/2.0f));
    int k2 = k/2;
    for(int v = 1;v<=k2;v++)
	{
	for(int u = 1;u<=k2;u++)
	    {
	    // bas droite
	    sum+=ptrDeviceNoyau[(ss+v*k)+u]*tex2D(textureRef,j+u,i+v).x;
	    // haut droite
	    sum+=ptrDeviceNoyau[(ss-v*k)+u]*tex2D(textureRef,j+u,i-v).x;
	    // bas gauche
	    sum+=ptrDeviceNoyau[(ss+v*k)-u]*tex2D(textureRef,j-u,i+v).x;
	    // haut gauche
	    sum+=ptrDeviceNoyau[(ss-v*k)-u]*tex2D(textureRef,j-u,i-v).x;
	    }
	// bras east
	sum+=ptrDeviceNoyau[ss+v]*tex2D(textureRef,j,i+v).x;
	// bras west
	sum+=ptrDeviceNoyau[ss-v]*tex2D(textureRef,j,i-v).x;
	// bras south
	sum+=ptrDeviceNoyau[ss+v*k]*tex2D(textureRef,j+v,i).x;
	// bras north
	sum+=ptrDeviceNoyau[ss-v*k]*tex2D(textureRef,j-v,i).x;
	}
    // centre
    sum+=ptrDeviceNoyau[ss]*tex2D(textureRef,j,i).x;
    ptrColor->x = sum;
    ptrColor->y = sum;
    ptrColor->z = sum;

    ptrColor->w = 255; // opaque
    }

__global__ void convolutionKernelMultiGPU(uchar4* ptrDevPixels, float* ptrDeviceNoyau, int k, int w, int h, float t)
    {
    extern __shared__ float convSM[];// 1 instance per block !

    //ConvolutionMathMultiGPU convMath = ConvolutionMathMultiGPU(w, h);

    const int TID = Indice2D::tid();
    const int TID_LOCAL = Indice2D::tidLocal();
    const int NB_THREAD = Indice2D::nbThread();

    const int WH=w*h;

    uchar4 color;

    int pixelI;
    int pixelJ;

    int s = TID_LOCAL;
    if(s < (k*k))
	convSM[s] = ptrDeviceNoyau[s];
    __syncthreads();

    s = TID;
    while (s < WH)
	{
	IndiceTools::toIJ(s, w, &pixelI, &pixelJ); // update (pixelI, pixelJ)
	colorIJMultiGPU(&color,convSM,k,pixelI, pixelJ, s); 	// update color
	ptrDevPixels[s] = color;
	s += NB_THREAD;
	}
    }

/*-------------------------*\
 |*	Constructeur	    *|
 \*-------------------------*/

ConvolutionMultiGPU::ConvolutionMultiGPU()
    {
    ConvolutionMultiGPU(1);
    }

ConvolutionMultiGPU::ConvolutionMultiGPU(const int NB_GPU)
    {
    // Inputs
    this->w = 640;
    this->h = 360;
    this->k = 9;
    this->NB_GPUS = NB_GPU;

    // Tools
    this->dg = dim3(32, 1, 1); // disons a optimiser
    this->db = dim3(256, 1, 1); // disons a optimiser
    this->t=0;

    //Outputs
    this->title="[API Image Cuda] : Convolution CUDA MultiGPU";
    //this->videoPath="/media/Data/Video/nasaFHD_short.avi";
    //this->videoTitle="NASA FHD SHORT";

    this->videoPath="/media/Data/Video/neilPryde.avi";
    this->videoTitle="neilPryde";

    size_t sizeOctets=w*h*sizeof(uchar4);
    HANDLE_ERROR( cudaHostAlloc ((void**) &(this->ptrHostMemory), sizeOctets,cudaHostAllocDefault ) );

    this->captureur = new CaptureVideo(videoPath,videoTitle,this->ptrHostMemory);

    const int N = k*k;
    sizeConvSM = N*sizeof(float);

    HANDLE_ERROR( cudaHostAlloc ((void**) &(this->ptrHostNoyau), N*sizeof(float),cudaHostAllocDefault ) );

    fillDetourage(ptrHostNoyau);

    sizeSM = 2*db.x*sizeof(uchar);
    sizeResult=2*dg.x*sizeof(uchar);
    ptrHostResult = (uchar**)malloc(NB_GPU*sizeof(uchar*));

    ptrDeviceNoyau = (float**)malloc(NB_GPU*sizeof(float*));
    ptrDevResult = (uchar**)malloc(NB_GPU*sizeof(uchar*));
    for(int i = 0;i<NB_GPU;i++)
	{
	ptrHostResult[i] = (uchar*) malloc(sizeResult);
	HANDLE_ERROR(cudaSetDevice(i));
	HANDLE_ERROR(cudaMalloc((void**)&ptrDeviceNoyau[i],N*sizeof(float)));
	// first contains min of each block, then max of each block
	HANDLE_ERROR(cudaMalloc((void**)&ptrDevResult[i], sizeResult));
	HANDLE_ERROR(cudaMemcpy(ptrDeviceNoyau[i],ptrHostNoyau,N*sizeof(float),cudaMemcpyHostToDevice));
	}
    HANDLE_ERROR(cudaSetDevice(0));

    textureRef.filterMode= cudaFilterModePoint;
    textureRef.normalized=false; //ou true coordonnée texture (i,j)
    textureRef.addressMode[0] = cudaAddressModeClamp;
    textureRef.addressMode[1] = cudaAddressModeClamp;

    pitch = w * sizeof(uchar4); //taille en octets d'une ligne
    channelDesc = cudaCreateChannelDesc<uchar4>();

    ptrDevMultiGPUImage = (uchar4**)malloc(NB_GPU*sizeof(uchar4*));
    stream = new cudaStream_t[NB_GPU];
    for(int i = 0;i<NB_GPU;i++)
	{
	HANDLE_ERROR(cudaSetDevice(i));
	cudaStreamCreate(&stream[i]);
	}
    HANDLE_ERROR(cudaSetDevice(0));
    //Device::p2pEnableALL();
    //cout << endl<<"[CBI] Convolution dt =" << dt << endl;
    }

ConvolutionMultiGPU::~ConvolutionMultiGPU()
    {
    free(ptrHostResult);
    cudaFree(ptrDevResult);
    for(int i = 0;i<NB_GPUS;i++)
	{
	cudaSetDevice(i);
	cudaStreamDestroy(stream[i]);
	cudaDeviceReset();
	}
    }

/*-------------------------*\
 |*	Methode		    *|
 \*-------------------------*/

/**
 * Noyau detourage 9x9
 */
void ConvolutionMultiGPU::fillDetourage(float* ptrNoyau)
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

/**
 * Override
 * Call periodicly by the API
 */
void ConvolutionMultiGPU::animationStep()
    {
    //t+=dt;
    }

/**
 * Override
 */
void ConvolutionMultiGPU::runGPU(uchar4* ptrDevPixels)
    {
    Chronos chrono;
    HANDLE_ERROR(cudaSetDevice(0));
    Mat matImage = captureur->capturer();
    uchar4* image = CaptureVideo::castToUChar4(&matImage);

    HANDLE_ERROR(cudaMemcpy(ptrDevPixels,image,(w*h)*sizeof(ptrDevPixels[0]),cudaMemcpyHostToDevice));

    //printf("Image to Grey\n");
    //colorToGreyMultiGPU<<<dg,db>>>(ptrDevPixels,w,h);
    //HANDLE_ERROR(cudaDeviceSynchronize());

    //printf("Convolution on grey image\n");
    //printf("Binding texture\n");
    colorToGreyMultiGPU<<<dg,db,0,stream[0]>>>(ptrDevPixels,w,h/NB_GPUS);
    cudaBindTexture2D(NULL, textureRef,ptrDevPixels,channelDesc,w,(h/NB_GPUS),pitch);
    convolutionKernelMultiGPU<<<dg,db,sizeConvSM,stream[0]>>>(ptrDevPixels,ptrDeviceNoyau[0],k,w,h/NB_GPUS,t);
    findMinMaxMultiGPU<<<dg,db,sizeSM,stream[0]>>>(ptrDevPixels,ptrDevResult[0],w,h/NB_GPUS);
    HANDLE_ERROR(cudaMemcpyAsync(ptrHostResult[0], ptrDevResult[0], sizeResult, cudaMemcpyDeviceToHost,stream[0]));
    for(int i = 1;i<NB_GPUS;i++)
	{
	HANDLE_ERROR(cudaSetDevice(i));
	if(i==NB_GPUS-1)
	    {
	    // portion of image + offset for convolution
	    cudaMalloc((void**)&ptrDevMultiGPUImage[i-1],((w*h/NB_GPUS)+(k*w/2))*sizeof(uchar4));
	    cudaMemcpyAsync(ptrDevMultiGPUImage[i-1],ptrDevPixels+i*(w*h/NB_GPUS)-(k*w/2),((w*h/NB_GPUS)+(k*w/2))*sizeof(uchar4),
		    cudaMemcpyDeviceToDevice,stream[i]);
	    colorToGreyMultiGPU<<<dg,db,0,stream[i]>>>(ptrDevMultiGPUImage[i-1],w,((h/NB_GPUS)+(k/2)));
	    //cudaStreamSynchronize(stream[i]);
	    HANDLE_ERROR(cudaPeekAtLastError());
	    cudaBindTexture2D(NULL, textureRef,ptrDevMultiGPUImage[i-1],channelDesc,w,((h/NB_GPUS)+(k/2)),pitch);
	    HANDLE_ERROR(cudaPeekAtLastError());
	    convolutionKernelMultiGPU<<<dg,db,sizeConvSM,stream[i]>>>(ptrDevMultiGPUImage[i-1],ptrDeviceNoyau[i],k,w,((h/NB_GPUS)+(k/2)),t);
	    HANDLE_ERROR(cudaPeekAtLastError());
	    findMinMaxMultiGPU<<<dg,db,sizeSM,stream[i]>>>(ptrDevMultiGPUImage[i-1],ptrDevResult[i],w,((h/NB_GPUS)+(k/2)));
	    HANDLE_ERROR(cudaMemcpyAsync(ptrHostResult[i], ptrDevResult[i], sizeResult, cudaMemcpyDeviceToHost,stream[i]));
	    }
	else
	    {
	    // portion of image + offset for convolution
	    cudaMalloc((void**)&ptrDevMultiGPUImage[i-1],((w*h/NB_GPUS)+2*(k*w/2))*sizeof(uchar4));
	    cudaMemcpyAsync(ptrDevMultiGPUImage[i-1],ptrDevPixels+i*(w*h/NB_GPUS)-(k*w/2),((w*h/NB_GPUS)+2*(k*w/2))*sizeof(uchar4),
		    cudaMemcpyDeviceToDevice,stream[i]);
	    //cudaStreamSynchronize(stream[i]);
	    colorToGreyMultiGPU<<<dg,db,0,stream[i]>>>(ptrDevMultiGPUImage[i-1],w,((h/NB_GPUS)+2*(k/2)));
	    HANDLE_ERROR(cudaPeekAtLastError());
	    cudaBindTexture2D(NULL, textureRef,ptrDevMultiGPUImage[i-1],channelDesc,w,((h/NB_GPUS)+2*(k/2)),pitch);
	    HANDLE_ERROR(cudaPeekAtLastError());
	    convolutionKernelMultiGPU<<<dg,db,sizeConvSM,stream[i]>>>(ptrDevMultiGPUImage[i-1],ptrDeviceNoyau[i],k,w,((h/NB_GPUS)+2*(k/2)),t);
	    HANDLE_ERROR(cudaPeekAtLastError());
	    findMinMaxMultiGPU<<<dg,db,sizeSM,stream[i]>>>(ptrDevMultiGPUImage[i-1],ptrDevResult[i],w,((h/NB_GPUS)+2*(k/2)));
	    HANDLE_ERROR(cudaMemcpyAsync(ptrHostResult[i], ptrDevResult[i], sizeResult, cudaMemcpyDeviceToHost,stream[i]));
	    }

	}
    uchar max = 0;
    uchar min = 255;
    float a = 0;
    float b = 0;
    for(int i = 0;i<NB_GPUS;i++)
	{
	HANDLE_ERROR(cudaSetDevice(i));
	HANDLE_ERROR(cudaStreamSynchronize(stream[i]));
	}
    for(int i = 0;i<NB_GPUS;i++)
	{
	for(int j = 0;j<dg.x;j++)
	    {
	    uchar crt = ptrHostResult[i][j];
	    if(crt < min)
		min = crt;
	    crt = ptrHostResult[i][j+dg.x];
	    if(crt > max)
		max = crt;
	    }
	// affine transformation
	a = 255.0f/(float)(max-min);
	b = 0;
	if(min != 0)
	    b = 255.0f/((-max/(float)min)+1.0f);
	}
    HANDLE_ERROR(cudaSetDevice(0));
    affineTransformMultiGPU<<<dg,db,0,stream[0]>>>(ptrDevPixels, a, b, w, h/NB_GPUS,0);
    for(int i = 1;i<NB_GPUS;i++)
	{
	HANDLE_ERROR(cudaSetDevice(i));
	if(i==NB_GPUS-1)
	    {
	    affineTransformMultiGPU<<<dg,db,0,stream[i]>>>(ptrDevMultiGPUImage[i-1], a, b, w, ((h/NB_GPUS)+(k/2)),0);
	    }
	else if(i > 0)
	    {
	    affineTransformMultiGPU<<<dg,db,0,stream[i]>>>(ptrDevMultiGPUImage[i-1], a, b, w, ((h/NB_GPUS)+2*(k/2)),0);
	    }
	}
    for(int i = 0;i<NB_GPUS;i++)
	{
	HANDLE_ERROR(cudaSetDevice(i));
	HANDLE_ERROR(cudaStreamSynchronize(stream[i]));
	if(i>0)
	    cudaMemcpyAsync(ptrDevPixels+i*(w*h/NB_GPUS),ptrDevMultiGPUImage[i-1]+(k*w/2),((w*h/NB_GPUS))*sizeof(uchar4),cudaMemcpyDeviceToDevice,
		    stream[i]);
	}
    for(int i = 0;i<NB_GPUS;i++)
	{
	HANDLE_ERROR(cudaSetDevice(i));
	HANDLE_ERROR(cudaStreamSynchronize(stream[i]));
	}
    //HANDLE_ERROR(cudaStreamSynchronize(stream[0]));
    HANDLE_ERROR(cudaSetDevice(0));

    //printf("Rescaling colors\n");
    //    findMinMaxMultiGPU<<<dg,db,sizeSM>>>(ptrDevPixels,ptrDevResult,w,h);
    //    HANDLE_ERROR(cudaMemcpy(ptrHostResult, ptrDevResult, sizeResult, cudaMemcpyDeviceToHost));
    //printf("min: %d, max: %d\n",min,max);
    chrono.stop();
    cout << "ElapseTime:  " << chrono.getDeltaTime()<< " (s)" << endl;
    }

/*--------------*\
 |*	get	 *|
 \*--------------*/

/**
 * Override
 */
float ConvolutionMultiGPU::getT(void)
    {
    return t;
    }

/**
 * Override
 */
int ConvolutionMultiGPU::getW(void)
    {
    return w;
    }

/**
 * Override
 */
int ConvolutionMultiGPU::getH(void)
    {
    return  h;
    }

/**
 * Override
 */
string ConvolutionMultiGPU::getTitle(void)
    {
    return title;
    }

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/


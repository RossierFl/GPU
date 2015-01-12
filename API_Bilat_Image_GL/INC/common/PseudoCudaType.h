#ifndef CUDA_PSEUDO_TYPE_H_
#define CUDA_PSEUDO_TYPE_H_

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

namespace cpu
    {

    struct float2
	{
	    float x;
	    float y;
	};

    struct float3
	{
	    float x;
	    float y;
	    float z;
	};

    struct uchar4
	{
	    unsigned char x;
	    unsigned char y;
	    unsigned char z;
	    unsigned char w;
	};

    }

#endif 

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/

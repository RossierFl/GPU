#ifndef CUDA_TYPE_CPU_H_
#define CUDA_TYPE_CPU_H_

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

namespace cpu
    {

    //#define uchar unsigned char
    typedef unsigned char uchar; //Mieux, en plus tu as la coloration synthaxique

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
	    uchar x;
	    uchar y;
	    uchar z;
	    uchar w;
	};
    }

#endif 

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/

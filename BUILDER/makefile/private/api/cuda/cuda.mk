# Version 	: 0.0.4
# Author 	: Cedric.Bilat@he-arc.ch
#

ifndef __API_CUDA_MK__
__API_CUDA_MK__=true

##########################################
#   		 Cuda 		  	 			 #
##########################################



#########################
# 		 WINDOWS		#
#########################

ifeq ($(OS),Win)

############
# Visual   #
############

ifeq ($(COMPILATEUR),VISUAL)

	#compil
	#SRC_AUX+= ${CUDA_INC_ROOT} #ko
	NVCCFLAGS+= -I${CUDA_INC_ROOT}
	
	#link
	NVCCLDFLAGS+= -L${CUDA_LIB}

	#NVCCLDFLAGS+= -lcublas_device
	NVCCLDFLAGS+= -lcublas
	NVCCLDFLAGS+= -lcuda
	NVCCLDFLAGS+= -lcudadevrt
	NVCCLDFLAGS+= -lcudart
	NVCCLDFLAGS+= -lcudart_static
	NVCCLDFLAGS+= -lcufft
	NVCCLDFLAGS+= -lcufftw
	NVCCLDFLAGS+= -lcurand
	NVCCLDFLAGS+= -lcusparse
	NVCCLDFLAGS+= -lnppc
	NVCCLDFLAGS+= -lnppi
	NVCCLDFLAGS+= -lnpps	
	NVCCLDFLAGS+= -lnvblas
	NVCCLDFLAGS+= -lnvcuvid
	NVCCLDFLAGS+= -lOpenCL
	
endif

endif

#########################
# 		 LINUX			#
#########################

ifeq ($(OS),Linux)

############
# common   #
############

	#compil
	NVCCFLAGS+= -I$(subst :, -I,${CUDA_INC})
	
	#link
	NVCCLDFLAGS+= -L$(subst :, -L,${CUDA_LIB})
	NVCCLDFLAGS+= -l$(subst :, -l,${CUDA_LIBRARIES}) 
	
############
# GCC   #
############

ifeq  ($(COMPILATEUR),g++)

	#rien

endif
	
############
# ARM   #
############

ifeq  ($(ARCH),arm)
	#LDFLAGS+= -L$(subst :, -L,${CUDA_LIB})
	#RPATH_LINK+=${CUDA_LIB}
endif

endif#end os

##########################################
#   			 END 		   			 #
##########################################

endif#__API_CUDA_MK__


# Version 	: 0.0.6
# Author 	: Cedric.Bilat@he-arc.ch
#
#
# https://software.intel.com/en-us/articles/intel-mkl-link-line-advisor/
#

ifndef __API_CUDA_MKL_MK__
__API_CUDA_MKL_MK__=true

##########################################
#   		MKL	Cuda 		   			 #
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
	NVCCFLAGS+= -I$(subst ;, -I,${MKL_INCLUDE})
	
	#link
	NVCCLDFLAGS+= mkl_intel_lp64_dll.lib
	NVCCLDFLAGS+= mkl_core_dll.lib
	NVCCLDFLAGS+= mkl_intel_thread_dll.lib
	
	NVCCLDFLAGS+= -L$(subst ;, -L,${MKL_LIB64}) 
	
	#runtime
	API_BIN+=${MKL_BIN}
		
endif

endif



#########################
# 		 LINUX			#
#########################

ifeq ($(OS),Linux)

############
# GCC   #
############

ifeq  ($(COMPILATEUR),g++)

	#compilation
	#NVCCFLAGS+= -I/opt/intel/mkl/include
	NVCCFLAGS+= -I$(subst :, -I,${MKL_INC})
	
	NVCCFLAGS+= -DMKL_ILP64 
	#TODO a tester
	#Intel fourni 2 fft, la sienne et une implementation de la libraire FFTW
	#POur linker la version FFTW, utilisez les flag ci-dessous
	#NVCCFLAGS+= -lfftw3_omp 
	#NVCCFLAGS+= -lfftw3
	
	
	
	#link
	#NVCCLDFLAGS+= -L/opt/intel/mkl/lib/intel64 
	NVCCLDFLAGS+= -L$(subst :, -L,${MKL_LIB}) 
	NVCCLDFLAGS+= -l$(subst :, -l,${MKL_LIB_GCC_LIBRARIES}) 
	
	#NVCCLDFLAGS+= -lmkl_intel_ilp64
	#NVCCLDFLAGS+= -lmkl_gnu_thread
	#NVCCLDFLAGS+= -lmkl_core

	#NVCCLDFLAGS+= -ldl
	#NVCCLDFLAGS+= -lpthread
	#NVCCLDFLAGS+= -lm
	
	#runtime
	API_BIN+= $(MKL_LIB)
		
endif

############
# ARM   #
############

ifeq  ($(ARCH),arm)
	#pas possible
endif

endif

##########################################
#   			 END 		   			 #
##########################################

endif#__API_CUDA_MKL_MK__

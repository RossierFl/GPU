# Version 	: 0.0.4
# Date		: 2.06.2013
# Author 	: Cedric.Bilat@he-arc.ch
#

ifndef __API_CUDA_OPEN_MP_MK__
__API_CUDA_OPEN_MP_MK__=true


##########################################
#   			 OpenCV Cuda   			 #
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
	CXXFLAGS+= /openmp
		
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
	override CXXFLAGS:= -fopenmp ${CXXFLAGS}
	#pour arm -fopenmp avant!
	
	#link
	NVCCLDFLAGS+= -lgomp#version gcc
	#NVCCLDFLAGS+= -liomp5#ou version intel
	
	#NVCCLDFLAGS+= -l$(subst :, -l,${OPENMP_LIBRARIES})
	
endif

############
# ARM   #
############

ifeq  ($(ARCH),arm)
	
endif


endif

##########################################
#   			 END 		   			 #
##########################################

endif#__API_CUDA_OPEN_MP_MK__


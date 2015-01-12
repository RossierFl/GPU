# Version 	: 0.0.4
# Author 	: Cedric.Bilat@he-arc.ch
#

ifndef __API_CUDA_JNI_HIDDEN_MK__
__API_CUDA_JNI_MK__=true

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

	NVCCFLAGS+= -I${JAVA_HOME_64}/include
	NVCCFLAGS+= -I${JAVA_HOME_64}/include/win32
	SRC_AUX+=${JAVA_HOME_64}/lib
endif

endif#windows

#########################
# 		 LINUX			#
#########################

ifeq ($(OS),Linux)

############
# common   #
############

	#compilation
	NVCCFLAGS+= -I$(subst :, -I,${JAVA_INC})
	
	#linkage
	NVCCLDFLAGS+= -L$(subst :, -L,${JAVA_LIB})
	NVCCLDFLAGS+= -l$(subst :, -l,${JAVA_LIBRARIES})

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
	RPATH_LINK+=${JAVA_LIB}
endif

endif#end os

##########################################
#   			 END 		   			 #
##########################################

endif#__API_CUDA_JNI_MK__


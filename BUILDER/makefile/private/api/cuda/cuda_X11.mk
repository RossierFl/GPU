# Version 	: 0.0.4
# Author 	: Cedric.Bilat@he-arc.ch
#

ifndef __API_CUDA_X11_MK__
__API_CUDA_X11_MK__=true

##########################################
#   		x11	Cuda 		   			 #
##########################################

#linux only!

#########################
# 		 LINUX			#
#########################

ifeq ($(OS),Linux)

############
# common   #
############

	#compilation
	#NVCCFLAGS+= -I/usr/include/X11
	NVCCFLAGS+= -I$(subst :, -I,${X11_INC})

	#linkage
	#NVCCLDFLAGS+= -L/usr/lib/x86_64-linux-gnu
	#NVCCLDFLAGS+= -lX11 
	
	NVCCLDFLAGS+= -L$(subst :, -L,${X11_LIB})
	NVCCLDFLAGS+= -l$(subst :, -l,${X11_LIBRARIES}) 
	
############
# GCC   #
############

ifeq  ($(COMPILATEUR),g++)

#ien
		
endif

############
# ARM   #
############

ifeq  ($(ARCH),arm)
	#NVCCFLAGS+= -I$(subst :, -I,${X11_INC})
	#NVCCLDFLAGS+= -L$(subst :, -L,${X11_LIB})

	RPATH_LINK+=${X11_LIB}
endif

endif#end os

##########################################
#   			 END 		   			 #
##########################################

endif#__API_CUDA_X11_MK__


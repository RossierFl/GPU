# Version 	: 0.0.4
# Author 	: Cedric.Bilat@he-arc.ch
#

ifndef __API_CUDA_FREEGLUT_MK__
__API_CUDA_FREEGLUT_MK__=true


##########################################
#   		GL				   			 #
##########################################

#dependance
include ${API_CUDA}/cuda_GL.mk

API_FreeGlut=../API_FreeGlut

#compil

#########################
# 		 WINDOWS		#
#########################

ifeq ($(OS),Win)

SRC_AUX+= ${API_FreeGlut}/INC_WIN

############
# Visual   #
############

ifeq ($(COMPILATEUR),VISUAL)

	#link
	SRC_AUX+= ${API_FreeGlut}/LIB/visual
	
	#runtime
	API_BIN+= ${API_FreeGlut}/BIN/visual
	
endif

############
# Intel   #
############

ifeq  ($(COMPILATEUR),INTEL)

	#link
	SRC_AUX+= ${API_FreeGlut}/LIB/visual
	
	#runtime
	API_BIN+= ${API_FreeGlut}/BIN/visual
	
endif

############
# MINGW   #
############

ifeq  ($(COMPILATEUR),MINGW)
	
	#link
	SRC_AUX+= ${API_FreeGlut}/LIB/mingw
	
	#runtime
	API_BIN+= ${API_FreeGlut}/BIN/visual
	
endif

endif



#########################
# 		 LINUX			#
#########################

ifeq ($(OS),Linux)

############
# common   #
############

#link
NVCCLDFLAGS+= -l$(subst :, -l,${FREEGLUT_LIBRARIES}) 

############
# GCC   #
############

ifeq  ($(COMPILATEUR),g++)

	#rien
	
endif

############
# INTEL   #
############

ifeq  ($(COMPILATEUR),INTEL)

	#rien
	
endif

############
# ARM   #
############

ifeq  ($(ARCH),arm)
	NVCCFLAGS+= -I$(subst :, -I,${FREEGLUT_INC})
	NVCCLDFLAGS+= -L$(subst :, -L,${FREEGLUT_LIB})#car use freeglut system
	RPATH_LINK+=${FREEGLUT_LIB}
endif

endif#linux

##########################################
#   			 END 		   			 #
##########################################

endif#__API_CUDA_FREEGLUT_MK__


# Version 	: 0.0.4
# Author 	: Cedric.Bilat@he-arc.ch
#

ifndef __API_CUDA_GL_MK__
__API_CUDA_GL_MK__=true

##########################################
#   		GL				   			 #
##########################################

API_GL=../API_GL

#dependance
include ${API_CUDA}/cuda_X11.mk

#compil

#########################
# 		 WINDOWS		#
#########################

ifeq ($(OS),Win)

SRC_AUX+= ${API_GL}/INC_WIN

#pour #include <GL/glew.h>
override INC_PATH:=${INC_PATH} ${API_GL}/INC_WIN

############
# Visual   #
############

ifeq ($(COMPILATEUR),VISUAL)

	#link
	SRC_AUX+= ${API_GL}/LIB/visual
	ADD_LIBRARY_FILES+= kernel32.lib gdi32.lib user32.lib opengl32.lib glu32.lib
	
	#runtime
	API_BIN+= ${API_GL}/BIN/visual
	
endif

############
# Intel   #
############

ifeq  ($(COMPILATEUR),INTEL)

	#link
	SRC_AUX+= ${API_GL}/LIB/visual
	ADD_LIBRARY_FILES+= kernel32.lib gdi32.lib user32.lib opengl32.lib glu32.lib
	
	#runtime
	API_BIN+= ${API_GL}/BIN/visual
	
endif

############
# MINGW   #
############

ifeq  ($(COMPILATEUR),MINGW)
	
	#link
	SRC_AUX+= ${API_GL}/LIB/mingw
	ADD_LIBRARY_FILES+= kernel32 user32 gdi32 opengl32 glu32
	
	#runtime
	API_BIN+= ${API_GL}/BIN/visual
	
endif

endif



#########################
# 		 LINUX			#
#########################

ifeq ($(OS),Linux)

############
# common   #
############

NVCCLDFLAGS+= -l$(subst :, -l,${GL_LIBRARIES}) 

############
# GCC   #
############

ifeq  ($(COMPILATEUR),g++)

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
	NVCCFLAGS+= -I$(subst :, -I,${GL_INC})
	NVCCLDFLAGS+= -L$(subst :, -L,${GL_LIB})#car use freeglut system
	RPATH_LINK+=${GL_LIB}
endif

endif#linux

##########################################
#   			 END 		   			 #
##########################################

endif#__API_CUDA_GL_MK__

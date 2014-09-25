# Version 	: 0.0.4
# Author 	: Cedric.Bilat@he-arc.ch
#


ifndef __API_CUDA_Bilat_GL_MK__
__API_CUDA_Bilat_GL_MK__=true

##########################################
#   		CUDA Bilat GL	   			 #
##########################################


#dependance
include $(API_CUDA)/cuda.mk
include ${API_CUDA}/cuda_GL.mk
include ${API}/bilat_DLL_Tools.mk

API_Bilat_GL=../API_Bilat_GL

#compil
SRC_AUX+= ${API_Bilat_GL}/INC

#########################
# 		 WINDOWS		#
#########################

ifeq ($(OS),Win)

############
# Visual   #
############

ifeq ($(COMPILATEUR),VISUAL)

	#link
	SRC_AUX+= ${API_Bilat_GL}/LIB/visual
	
	#runtime
	API_BIN+= ${API_Bilat_GL}/BIN/visual
	
endif

############
# Intel   #
############

ifeq  ($(COMPILATEUR),INTEL)

	#link
	SRC_AUX+= ${API_Bilat_GL}/LIB/intelWin
	
	#runtime
	API_BIN+= ${API_Bilat_GL}/BIN/intelWin
	
endif

############
# MINGW   #
############

ifeq  ($(COMPILATEUR),MINGW)
	
	#link
	SRC_AUX+= ${API_Bilat_GL}/LIB/mingw
	
	#runtime
	API_BIN+= ${API_Bilat_GL}/BIN/mingw
	
endif

endif

#########################
# 		 LINUX			#
#########################

ifeq ($(OS),Linux)

############
# ARM   #
############

ifeq  ($(ARCH),arm)
	ARM_FOLDER="_arm"
else
	ARM_FOLDER=#
endif

############
# GCC   #
############

ifeq  ($(COMPILATEUR),g++)

	#link
	SRC_AUX+= ${API_Bilat_GL}/BIN/gcc${ARM_FOLDER}
	
	#runtime
	API_BIN+= ${API_Bilat_GL}/BIN/gcc${ARM_FOLDER}
	
endif

############
# INTEL   #
############

ifeq  ($(COMPILATEUR),INTEL)

	#link
	SRC_AUX+= ${API_Bilat_GL}/BIN/gcc${ARM_FOLDER}
	#SRC_AUX+= ${API_Bilat_GL}/BIN/intelLinux
	
	#runtime
	API_BIN+= ${API_Bilat_GL}/BIN/gcc${ARM_FOLDER}
	#API_BIN+= ${API_Bilat_GL}/BIN/intelLinux
	
endif

endif

##########################################
#   			 END 		   			 #
##########################################

endif#__API_CUDA_Bilat_GL_MK__
# Version 	: 0.0.4
# Author 	: Cedric.Bilat@he-arc.ch
#

ifndef __CUDA_API_BILAT_FREEGLUT_TOOLS_MK__
__CUDA_API_BILAT_FREEGLUT_TOOLS_MK__=true

##########################################
#   	Cuda Bilat FREEGLUT TOOLS        #
##########################################


#dependance
include $(API_CUDA)/cuda.mk
include $(API_CUDA)/cuda_OpenMP.mk
include ${API_CUDA}/cuda_freeGlut.mk

include $(API_CUDA)/cuda_bilat_Displayable.mk
include ${API}/bilat_DLL_Tools.mk

API_FreeGlutTools=../API_Bilat_FreeGlut_Tools

#compil
SRC_AUX+= ${API_FreeGlutTools}/INC

#########################
# 		 WINDOWS		#
#########################

ifeq ($(OS),Win)

############
# Visual   #
############

ifeq ($(COMPILATEUR),VISUAL)

	#link
	SRC_AUX+= ${API_FreeGlutTools}/LIB/visual
	
	#runtime
	API_BIN+= ${API_FreeGlutTools}/BIN/visual
	
endif

############
# Intel   #
############

ifeq  ($(COMPILATEUR),INTEL)

	#link
	SRC_AUX+= ${API_FreeGlutTools}/LIB/intelWin
	
	#runtime
	API_BIN+= ${API_FreeGlutTools}/BIN/intelWin
	
endif

############
# MINGW   #
############

ifeq  ($(COMPILATEUR),MINGW)
	
	#link
	SRC_AUX+= ${API_FreeGlutTools}/LIB/mingw
	
	#runtime
	API_BIN+= ${API_FreeGlutTools}/BIN/mingw
	
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
	SRC_AUX+= ${API_FreeGlutTools}/BIN/gcc${ARM_FOLDER}
	
	#runtime
	API_BIN+= ${API_FreeGlutTools}/BIN/gcc${ARM_FOLDER}

	
endif

############
# INTEL   #
############

ifeq  ($(COMPILATEUR),INTEL)

	#link
	SRC_AUX+= ${API_FreeGlutTools}/BIN/gcc${ARM_FOLDER}
	#SRC_AUX+= ${API_FreeGlutTools}/BIN/intelLinux
	
	#runtime
	API_BIN+= ${API_FreeGlutTools}/BIN/gcc${ARM_FOLDER}
	#SRC_AUX+= ${API_FreeGlutTools}/BIN/intelLinux
	
endif

endif

##########################################
#   			 END 		   			 #
##########################################

endif #__CUDA_API_BILAT_FREEGLUT_TOOLS_MK__


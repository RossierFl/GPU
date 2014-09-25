# Version 	: 0.0.4
# Author 	: Cedric.Bilat@he-arc.ch
#


ifndef __CUDA_API_Bilat_Graph_MK__
__CUDA_API_Bilat_Graph_MK__=true

##########################################
#   	CUDA BilatGraph		   			 #
##########################################

#dependance
include $(API_CUDA)/cuda.mk
include $(API_CUDA)/cuda_OpenMP.mk
include ${API_CUDA}/cuda_bilat_GL.mk
include $(API_CUDA)/cuda_bilat_Displayable.mk

API_Bilat_Graph=../API_Bilat_Graph2D

#compil
SRC_AUX+= ${API_Bilat_Graph}/INC
CODE_DEFINE_VARIABLES+= CBI_GRAPH_DLL

#########################
# 		 WINDOWS		#
#########################

ifeq ($(OS),Win)

############
# Visual   #
############

ifeq ($(COMPILATEUR),VISUAL)

	#link
	SRC_AUX+= ${API_Bilat_Graph}/LIB/visual
	
	#runtime
	API_BIN+= ${API_Bilat_Graph}/BIN/visual
	
endif

############
# Intel   #
############

ifeq  ($(COMPILATEUR),INTEL)

	#link
	SRC_AUX+= ${API_Bilat_Graph}/LIB/intelWin
	
	#runtime
	API_BIN+= ${API_Bilat_Graph}/BIN/intelWin
	
endif

############
# MINGW   #
############

ifeq  ($(COMPILATEUR),MINGW)
	
	#link
	SRC_AUX+= ${API_Bilat_Graph}/LIB/mingw
	
	#runtime
	API_BIN+= ${API_Bilat_Graph}/BIN/mingw
	
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
	SRC_AUX+= ${API_Bilat_Graph}/BIN/gcc${ARM_FOLDER}
	
	#runtime
	API_BIN+= ${API_Bilat_Graph}/BIN/gcc${ARM_FOLDER}
	
endif

############
# INTEL   #
############

ifeq  ($(COMPILATEUR),INTEL)

	#link
	SRC_AUX+= ${API_Bilat_Graph}/BIN/gcc${ARM_FOLDER}
	#SRC_AUX+= ${API_Bilat_Graph}/BIN/intelLinux
	
	#runtime
	API_BIN+= ${API_Bilat_Graph}/BIN/gcc${ARM_FOLDER}
	#API_BIN+= ${API_Bilat_Graph}/BIN/intelLinux
	
endif

endif

##########################################
#   			 END 		   			 #
##########################################

endif#__CUDA_API_Bilat_Graph_MK__
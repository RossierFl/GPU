# Version 	: 0.0.4
# Author 	: Cedric.Bilat@he-arc.ch
#


ifndef __API_Bilat_Graph2D_FreeGlut_MK__
__API_Bilat_Graph2D_FreeGlut_MK__=true

##########################################
#   		BilatGraph		   			 #
##########################################

#dependance
include ${API_CUDA}/cuda_bilat_Graph2D.mk
include ${API_CUDA}/cuda_bilat_FreeGlut_Tools.mk

API_Bilat_Graph2D_FreeGlut=../API_Bilat_Graph2D_FreeGlut

#compil
SRC_AUX+= ${API_Bilat_Graph2D_FreeGlut}/INC
CODE_DEFINE_VARIABLES+= 

#########################
# 		 WINDOWS		#
#########################

ifeq ($(OS),Win)

############
# Visual   #
############

ifeq ($(COMPILATEUR),VISUAL)

	#link
	SRC_AUX+= ${API_Bilat_Graph2D_FreeGlut}/LIB/visual
	
	#runtime
	API_BIN+= ${API_Bilat_Graph2D_FreeGlut}/BIN/visual
	
endif

############
# Intel   #
############

ifeq  ($(COMPILATEUR),INTEL)

	#link
	SRC_AUX+= ${API_Bilat_Graph2D_FreeGlut}/LIB/intelWin
	
	#runtime
	API_BIN+= ${API_Bilat_Graph2D_FreeGlut}/BIN/intelWin
	
endif

############
# MINGW   #
############

ifeq  ($(COMPILATEUR),MINGW)
	
	#link
	SRC_AUX+= ${API_Bilat_Graph2D_FreeGlut}/LIB/mingw
	
	#runtime
	API_BIN+= ${API_Bilat_Graph2D_FreeGlut}/BIN/mingw
	
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
	SRC_AUX+= ${API_Bilat_Graph2D_FreeGlut}/BIN/gcc${ARM_FOLDER}
	
	#runtime
	API_BIN+= ${API_Bilat_Graph2D_FreeGlut}/BIN/gcc${ARM_FOLDER}
	
endif

############
# INTEL   #
############

ifeq  ($(COMPILATEUR),INTEL)

	#link
	SRC_AUX+= ${API_Bilat_Graph2D_FreeGlut}/BIN/gcc${ARM_FOLDER}
	#SRC_AUX+= ${API_Bilat_Graph2D_FreeGlut}/BIN/intelLinux
	
	#runtime
	API_BIN+= ${API_Bilat_Graph2D_FreeGlut}/BIN/gcc${ARM_FOLDER}
	#API_BIN+= ${API_Bilat_Graph2D_FreeGlut}/BIN/intelLinux
	
endif

endif

##########################################
#   			 END 		   			 #
##########################################

endif#__API_Bilat_Graph2D_FreeGlut_MK__
# Version 	: 0.0.4
# Author 	: Cedric.Bilat@he-arc.ch
#

ifndef __CUDA_API_BILAT_DISPLAYABLE_MK__
__CUDA_API_BILAT_DISPLAYABLE_MK__=true

##########################################
#   Cuda Bilat DISPLAYABLE  			 #
##########################################


#dependance
include ${API}/bilat_DLL_Tools.mk

API_Bilat_Displayable=../API_Bilat_Displayable


#compil
SRC_AUX+= ${API_Bilat_Displayable}/INC
CODE_DEFINE_VARIABLES+=CBI_DISPLAYABLE_DLL

#########################
# 		 WINDOWS		#
#########################

ifeq ($(OS),Win)

############
# Visual   #
############

ifeq ($(COMPILATEUR),VISUAL)

	#link
	SRC_AUX+= ${API_Bilat_Displayable}/LIB/visual
	
	#runtime
	API_BIN+= ${API_Bilat_Displayable}/BIN/visual

endif

############
# Intel   #
############

ifeq  ($(COMPILATEUR),INTEL)

	#link
	SRC_AUX+= ${API_Bilat_Displayable}/LIB/intelWin
	
	#runtime
	API_BIN+= ${API_Bilat_Displayable}/BIN/intelWin

endif

############
# MINGW   #
############

ifeq  ($(COMPILATEUR),MINGW)
	
	#link
	SRC_AUX+= ${API_Bilat_Displayable}/LIB/mingw
	
	#runtime
	API_BIN+= ${API_Bilat_Displayable}/BIN/mingw

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
	SRC_AUX+= ${API_Bilat_Displayable}/BIN/gcc${ARM_FOLDER}
	
	#runtime
	API_BIN+= ${API_Bilat_Displayable}/BIN/gcc${ARM_FOLDER}

endif

############
# INTEL   #
############

ifeq  ($(COMPILATEUR),INTEL)

	SRC_AUX+= ${API_Bilat_Displayable}/BIN/gcc${ARM_FOLDER}
	
	#runtime
	API_BIN+= ${API_Bilat_Displayable}/BIN/gcc${ARM_FOLDER}

endif

endif

##########################################
#   			 END 		   			 #
##########################################

endif#__CUDA_API_BILAT_DISPLAYABLE_MK__


# Version 	: 0.0.4
# Author 	: Cedric.Bilat@he-arc.ch
#

ifndef __API_BILAT_IMAGE_FREEGLUT_TOOLS_MK__
__API_BILAT_IMAGE_FREEGLUT_TOOLS_MK__=true

##########################################
#   		Bilat IMAGE FREEGLUT		 #
##########################################


#dependance
include $(API)/bilat_Image_GL.mk
include $(API)/bilat_FreeGlut_Tools.mk

API_ImageFreeGlut=../API_Bilat_Image_FreeGlut

#compil
SRC_AUX+= ${API_ImageFreeGlut}/INC

#########################
# 		 WINDOWS		#
#########################

ifeq ($(OS),Win)

############
# Visual   #
############

ifeq ($(COMPILATEUR),VISUAL)

	#link
	SRC_AUX+= ${API_ImageFreeGlut}/LIB/visual
	
	#runtime
	API_BIN+= ${API_ImageFreeGlut}/BIN/visual
	
endif

############
# Intel   #
############

ifeq  ($(COMPILATEUR),INTEL)

	#link
	SRC_AUX+= ${API_ImageFreeGlut}/LIB/intelWin
	
	#runtime
	API_BIN+= ${API_ImageFreeGlut}/BIN/intelWin
	
endif

############
# MINGW   #
############

ifeq  ($(COMPILATEUR),MINGW)
	
	#link
	SRC_AUX+= ${API_ImageFreeGlut}/LIB/mingw
	
	#runtime
	API_BIN+= ${API_ImageFreeGlut}/BIN/mingw
	
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
	SRC_AUX+= ${API_ImageFreeGlut}/BIN/gcc${ARM_FOLDER}
	
	#runtime
	API_BIN+= ${API_ImageFreeGlut}/BIN/gcc${ARM_FOLDER}

	
endif

############
# INTEL   #
############

ifeq  ($(COMPILATEUR),INTEL)

	#link
	#SRC_AUX+= ${API_ImageFreeGlut}/BIN/gcc${ARM_FOLDER}
	SRC_AUX+= ${API_ImageFreeGlut}/BIN/intelLinux
	
	#runtime
	#API_BIN+= ${API_ImageFreeGlut}/BIN/gcc${ARM_FOLDER}
	API_BIN+= ${API_ImageFreeGlut}/BIN/intelLinux
	
endif

############
# ARM   #
############

ifeq  ($(ARCH),arm)
	#RPATH_LINK+=${API_ImageFreeGlut}/BIN/gcc
endif

endif

##########################################
#   			 END 		   			 #
##########################################

endif#__API_BILAT_IMAGE_FREEGLUT_TOOLS_MK__


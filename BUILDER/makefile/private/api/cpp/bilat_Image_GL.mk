# Version 	: 0.0.4
# Author 	: Cedric.Bilat@he-arc.ch
#


ifndef __API_BILAT_IMAGE_GL_MK__
__API_BILAT_IMAGE_GL_MK__=true

##########################################
#   		BilatGLImage	   			 #
##########################################


#dependance
include ${API}/GL.mk
include $(API)/openmp.mk
include ${API}/bilat_Displayable.mk

API_Bilat_Image=../API_Bilat_Image_GL

#compil
SRC_AUX+= ${API_Bilat_Image}/INC

#########################
# 		 WINDOWS		#
#########################

ifeq ($(OS),Win)

############
# Visual   #
############

ifeq ($(COMPILATEUR),VISUAL)

	#link
	SRC_AUX+= ${API_Bilat_Image}/LIB/visual
	
	#runtime
	API_BIN+= ${API_Bilat_Image}/BIN/visual
	
endif

############
# Intel   #
############

ifeq  ($(COMPILATEUR),INTEL)

	#link
	SRC_AUX+= ${API_Bilat_Image}/LIB/intelWin
	
	#runtime
	API_BIN+= ${API_Bilat_Image}/BIN/intelWin
	
endif

############
# MINGW   #
############

ifeq  ($(COMPILATEUR),MINGW)
	
	#link
	SRC_AUX+= ${API_Bilat_Image}/LIB/mingw
	
	#runtime
	API_BIN+= ${API_Bilat_Image}/BIN/mingw
	
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
	SRC_AUX+= ${API_Bilat_Image}/BIN/gcc${ARM_FOLDER}
	
	#runtime
	API_BIN+= ${API_Bilat_Image}/BIN/gcc${ARM_FOLDER}
	
endif

############
# INTEL   #
############

ifeq  ($(COMPILATEUR),INTEL)

	#link
	#SRC_AUX+= ${API_Bilat_Image}/BIN/gcc${ARM_FOLDER}
	SRC_AUX+= ${API_Bilat_Image}/BIN/intelLinux
	
	#runtime
	#API_BIN+= ${API_Bilat_Image}/BIN/gcc${ARM_FOLDER}
	API_BIN+= ${API_Bilat_Image}/BIN/intelLinux
	
endif

endif

##########################################
#   			 END 		   			 #
##########################################

endif#__API_BILAT_IMAGE_GL_MK__


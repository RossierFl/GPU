# Version 	: 0.0.4
# Author 	: Cedric.Bilat@he-arc.ch
#
ifndef __CUDA_API_Bilat_Image_JNI_MK__
__CUDA_API_Bilat_Image_JNI_MK__=true

##########################################
#   		Bilat Image JNI	   			 #
##########################################

#dependance
include ${API_CUDA}/cuda_bilat_Canvas_JNI.mk
include ${API_CUDA}/cuda_bilat_Image_GL.mk

API_Bilat_Image_JNI=../API_Bilat_Image_JNI

#compil
SRC_AUX+= ${API_Bilat_Image_JNI}/INC

#compil
SRC_AUX+= ${API_Bilat_Image_JNI}/INC

#########################
# 		 WINDOWS		#
#########################

ifeq ($(OS),Win)

############
# Visual   #
############

ifeq ($(COMPILATEUR),VISUAL)

	#link
	SRC_AUX+= ${API_Bilat_Image_JNI}/LIB/visual
	
	#runtime
	API_BIN+= ${API_Bilat_Image_JNI}/BIN/visual
	
endif

############
# Intel   #
############

ifeq  ($(COMPILATEUR),INTEL)

	#link
	SRC_AUX+= ${API_Bilat_Image_JNI}/LIB/intelWin
	
	#runtime
	API_BIN+= ${API_Bilat_Image_JNI}/BIN/intelWin
	
endif

############
# MINGW   #
############

ifeq  ($(COMPILATEUR),MINGW)
	
	#link
	SRC_AUX+= ${API_Bilat_Image_JNI}/LIB/mingw
	
	#runtime
	API_BIN+= ${API_Bilat_Image_JNI}/BIN/mingw
	
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
	SRC_AUX+= ${API_Bilat_Image_JNI}/BIN/gcc${ARM_FOLDER}
	
	#runtime
	API_BIN+= ${API_Bilat_Image_JNI}/BIN/gcc${ARM_FOLDER}
	
endif

############
# INTEL   #
############

ifeq  ($(COMPILATEUR),INTEL)

	#link
	SRC_AUX+= ${API_Bilat_Image_JNI}/BIN/gcc${ARM_FOLDER}
	#SRC_AUX+= ${API_Bilat_Image_JNI}/BIN/intelLinux
	
	#runtime
	API_BIN+= ${API_Bilat_Image_JNI}/BIN/gcc${ARM_FOLDER}
	#API_BIN+= ${API_Bilat_Image_JNI}/BIN/intelLinux
	
endif

endif

##########################################
#   			 END 		   			 #
##########################################

endif#__CUDA_API_Bilat_Image_JNI_MK__


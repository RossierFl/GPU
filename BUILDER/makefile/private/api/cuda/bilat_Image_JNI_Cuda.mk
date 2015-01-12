# Version 	: 0.0.4
# Author 	: Cedric.Bilat@he-arc.ch
#

ifndef __API_CUDA_BILAT_IMAGE_JNI_CUDA_MK__
__API_CUDA_BILAT_IMAGE_JNI_CUDA_MK__=true

##########################################
#   		BilatImageJNI_Cuda			 #
##########################################


#dependance
include $(API_CUDA)/bilat_Image_GL_Cuda.mk
include ${API_CUDA}/cuda_bilat_Image_JNI.mk


API_Bilat_Image_JNI_Cuda=../API_Bilat_Image_JNI_Cuda

#compil
SRC_AUX+= ${API_Bilat_Image_JNI_Cuda}/INC

#########################
# 		 WINDOWS		#
#########################

ifeq ($(OS),Win)

############
# Visual   #
############

ifeq ($(COMPILATEUR),VISUAL)

	#link
	SRC_AUX+= ${API_Bilat_Image_JNI_Cuda}/LIB/visual
	
	#runtime
	API_BIN+= ${API_Bilat_Image_JNI_Cuda}/BIN/visual
	
endif

############
# Intel   #
############

ifeq  ($(COMPILATEUR),INTEL)

	#link
	SRC_AUX+= ${API_Bilat_Image_JNI_Cuda}/LIB/visual
	
	#runtime
	API_BIN+= ${API_Bilat_Image_JNI_Cuda}/BIN/visual
	
endif

############
# MINGW   #
############

ifeq  ($(COMPILATEUR),MINGW)
	
	#link
	#TODO
	
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
	SRC_AUX+= ${API_Bilat_Image_JNI_Cuda}/BIN/gcc${ARM_FOLDER}
	
	#runtime
	API_BIN+= ${API_Bilat_Image_JNI_Cuda}/BIN/gcc${ARM_FOLDER}

	
endif

############
# INTEL   #
############

ifeq  ($(COMPILATEUR),INTEL)

	#link
	SRC_AUX+= ${API_Bilat_Image_JNI_Cuda}/BIN/gcc${ARM_FOLDER}
	
	#runtime
	API_BIN+= ${API_Bilat_Image_JNI_Cuda}/BIN/gcc${ARM_FOLDER}
	
endif

endif

##########################################
#   			 END 		   			 #
##########################################

endif#__API_CUDA_BILAT_IMAGE_JNI_CUDA_MK__
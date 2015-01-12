# Version 	: 0.0.4
# Author 	: Cedric.Bilat@he-arc.ch
#


ifndef __API_Bilat_Canvas_JNI_MK__
__API_Bilat_Canvas_JNI_MK__=true

##########################################
#   		Bilat Canvas JNI	   			 #
##########################################


#dependance
include $(API)/jni_hidden.mk
include ${API}/GL.mk
include ${API}/bilat_Displayable.mk

API_Bilat_Canvas_JNI=../API_Bilat_Canvas_JNI

#compil
SRC_AUX+= ${API_Bilat_Canvas_JNI}/INC

#########################
# 		 WINDOWS		#
#########################

ifeq ($(OS),Win)

############
# Visual   #
############

ifeq ($(COMPILATEUR),VISUAL)

	#link
	SRC_AUX+= ${API_Bilat_Canvas_JNI}/LIB/visual
	
	#runtime
	API_BIN+= ${API_Bilat_Canvas_JNI}/BIN/visual
	
endif

############
# Intel   #
############

ifeq  ($(COMPILATEUR),INTEL)

	#link
	SRC_AUX+= ${API_Bilat_Canvas_JNI}/LIB/intelWin
	
	#runtime
	API_BIN+= ${API_Bilat_Canvas_JNI}/BIN/intelWin
	
endif

############
# MINGW   #
############

ifeq  ($(COMPILATEUR),MINGW)
	
	#link
	SRC_AUX+= ${API_Bilat_Canvas_JNI}/LIB/mingw
	
	#runtime
	API_BIN+= ${API_Bilat_Canvas_JNI}/BIN/mingw
	
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
	ADD_LIBRARY_FILES+= jawt c
	CXXFLAGS+= -fpermissive
	#link
	SRC_AUX+= ${API_Bilat_Canvas_JNI}/BIN/gcc${ARM_FOLDER}
	
	#runtime
	API_BIN+= ${API_Bilat_Canvas_JNI}/BIN/gcc${ARM_FOLDER}
	
endif

############
# INTEL   #
############

ifeq  ($(COMPILATEUR),INTEL)

	#link
	SRC_AUX+= ${API_Bilat_Canvas_JNI}/BIN/gcc${ARM_FOLDER}
	#SRC_AUX+= ${API_Bilat_Canvas_JNI}/BIN/intelLinux
	
	#runtime
	API_BIN+= ${API_Bilat_Canvas_JNI}/BIN/gcc${ARM_FOLDER}
	#API_BIN+= ${API_Bilat_Canvas_JNI}/BIN/intelLinux
	
endif

endif

##########################################
#   			 END 		   			 #
##########################################

endif#__API_Bilat_Canvas_JNI_MK__

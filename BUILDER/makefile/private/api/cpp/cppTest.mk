# Version 	: 0.0.4
# Author 	: Cedric.Bilat@he-arc.ch
#

ifndef __API_CPP_TEST_MK__
__API_CPP_TEST_MK__=true

##########################################
#   			 cpptest	   			 #
##########################################

API_CppTest=../API_CppTest

TAKE_CPP_TEST_SRC=true

ifdef TAKE_CPP_TEST_SRC
	SRC_AUX+= ${API_CppTest}/SRC
else

#########################
# 	COMMOM ALL OS		#
#########################

#compil
SRC_AUX+= ${API_CppTest}/INC

#########################
# 		 WINDOWS		#
#########################

ifeq ($(OS),Win)

############
# Visual   #
############

ifeq ($(COMPILATEUR),VISUAL)

	#link
	SRC_AUX+= ${API_CppTest}/LIB_STATIC/visual
	
endif

############
# Intel   #
############

ifeq  ($(COMPILATEUR),INTEL)

	#link
	SRC_AUX+= ${API_CppTest}/LIB_STATIC/intelWin
endif

############
# MINGW   #
############

ifeq  ($(COMPILATEUR),MINGW)
	
	#link
	SRC_AUX+= ${API_CppTest}/LIB_STATIC/mingw
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
	SRC_AUX+= ${API_CppTest}/LIB_STATIC/gcc${ARM_FOLDER}
	
endif

############
# INTEL   #
############

ifeq  ($(COMPILATEUR),INTEL)

	#link 
	SRC_AUX+= ${API_CppTest}/LIB_STATIC/intelLinux${ARM_FOLDER}
	
endif

endif

endif
##########################################
#   			 END 		   			 #
##########################################

endif#__API_CPP_TEST_MK__


# Version 	: 0.0.4
# Author 	: Cedric.Bilat@he-arc.ch
#


ifndef __API_CUDA_BILAT_TOOLS_MK__
__API_CUDA_BILAT_TOOLS_MK__=true


##########################################
#   		Bilat CUDA TOOLS   			 #
##########################################


API_Bilat_Tools_Cuda=../API_Bilat_Tools_Cuda

#compil
SRC_AUX+= ${API_Bilat_Tools_Cuda}/INC

#########################
# 		 WINDOWS		#
#########################

ifeq ($(OS),Win)

############
# Visual   #
############

ifeq ($(COMPILATEUR),VISUAL)

	#link
	SRC_AUX+=
	
	#runtime
	API_BIN+=
	
endif

############
# Intel   #
############

ifeq  ($(COMPILATEUR),INTEL)

	#link
	SRC_AUX+= 
	
	#runtime
	API_BIN+=
	
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
	SRC_AUX+=
	
	#runtime
	API_BIN+=
	
endif

############
# INTEL   #
############

ifeq  ($(COMPILATEUR),INTEL)

	#link
	SRC_AUX+=
	
	#runtime
	API_BIN+=
	
endif

endif

##########################################
#   			 END 		   			 #
##########################################

endif#__API_CUDA_BILAT_TOOLS_MK__


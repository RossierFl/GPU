# Version 	: 0.0.4
# Author 	: Cedric.Bilat@he-arc.ch
#

ifndef __API_CUDA_OPEN_CV_MK__
__API_CUDA_OPEN_CV_MK__=true

##########################################
#   			 OpenCV Cuda   			 #
##########################################


#########################
# 		 WINDOWS		#
#########################

ifeq ($(OS),Win)

############
# Visual   #
############

ifeq ($(COMPILATEUR),VISUAL)

	##############
	#Version full
	##############
	
	#compil
	#SRC_AUX+= ${OPENCV64_INC}	#ok
	#NVCCFLAGS+= -I${OPENCV64_INC} 	#ko car sous folder

	#link
	#SRC_AUX+= ${OPENCV64_VISUAL_LIB}			#ok
	#NVCCLDFLAGS+= -L${OPENCV64_VISUAL_LIB} 	#embettant il faut lister lib now -lxxx

	##############
	#Version light 
	##############
		
	#compilation ok
	NVCCFLAGS+= -I${OPENCV64_INC}
	NVCCFLAGS+= -I${OPENCV64_INC_CV2}
	NVCCFLAGS+= -I${OPENCV64_INC_CV2}/highgui
	NVCCFLAGS+= -I${OPENCV64_INC_CV2}/core
	NVCCFLAGS+= -I${OPENCV64_INC_CV2}/flann
	NVCCFLAGS+= -I${OPENCV64_INC_CV2}/imgproc
	NVCCFLAGS+= -I${OPENCV64_INC_CV2}/video

#CXXFLAGS : ko

	#link ok
	NVCCLDFLAGS+= -L${OPENCV64_VISUAL_LIB}
	NVCCLDFLAGS+= -lopencv_highgui249 
	NVCCLDFLAGS+= -lopencv_core249
	NVCCLDFLAGS+= -lopencv_imgproc249
	
	#runtime
	API_BIN+= ${OPENCV64_VISUAL_BIN}
	
	# ko avec 
	#	CXXFLAGS
	#	CXXLDFLAGS
	 
endif

endif

#########################
# 		 LINUX			#
#########################

ifeq ($(OS),Linux)

############
# common   #
############

	#compilation
	#OPENCV2_INC:=/usr/include/opencv2#
	NVCCFLAGS+= -I$(subst :, -I,${OPENCV_INC})
	
	#link
	#NVCCLDFLAGS+= -L$(subst :, -L,${OPENCV_LIB})#pas besoin car system
	NVCCLDFLAGS+= -l$(subst :, -l,${OPENCV_LIBRARIES}) 
	#NVCCLDFLAGS+= -L$(subst :, -L,${OPENCV_LIB})#pas ici. car OPENCV_LIB pas define, install avec apt-get install

	# aussi ok avec 
	#	CXXFLAGS
	#	CXXLDFLAGS

############
# GCC   #
############

ifeq  ($(COMPILATEUR),g++)

	#rien
	
endif	

############
# ARM   #
############

ifeq  ($(ARCH),arm)
	NVCCLDFLAGS+= -L$(subst :, -L,${OPENCV_LIB})
	#RPATH_LINK+=${OPENCV_LIB}
endif

endif#end os

##########################################
#   			 END 		   			 #
##########################################

endif#__API_CUDA_OPEN_CV_MK__


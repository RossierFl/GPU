# Version 	: 0.0.5
# Author 	: Cedric.Bilat@he-arc.ch
#

ifndef __API_OPEN_CV_MK__
__API_OPEN_CV_MK__=true

##########################################
#   			 OpenCV		   			 #
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
	#SRC_AUX+= ${OPENCV64_INC} #ok
	#CXXFLAGS+= -I${OPENCV64_INC} #ko car sous folder

	#link
	#SRC_AUX+= ${OPENCV64_VISUAL_LIB}#ok
	#LDFLAGS_AUX+= /LIBPATH:${OPENCV64_VISUAL_LIB} #embettant il faut lister lib now -lxxx
	#LDFLAGS_AUX+= opencv_highgui244.lib
	#LDFLAGS_AUX+= opencv_core244.lib
	#LDFLAGS_AUX+= opencv_imgproc244.lib
	
	##############
	#Version light 
	##############
	
	#compilation ok
	CXXFLAGS+= -I${OPENCV64_INC}
	CXXFLAGS+= -I${OPENCV64_INC_CV2}
	CXXFLAGS+= -I${OPENCV64_INC_CV2}/highgui
	CXXFLAGS+= -I${OPENCV64_INC_CV2}/core
	CXXFLAGS+= -I${OPENCV64_INC_CV2}/flann
	CXXFLAGS+= -I${OPENCV64_INC_CV2}/imgproc
	CXXFLAGS+= -I${OPENCV64_INC_CV2}/video

	#link ok : 
	#LDFLAGS_AUX+=  /LIBPATH:${OPENCV64_VISUAL_LIB_STATIC} #ko
	LDFLAGS_AUX+=  /LIBPATH:${OPENCV64_VISUAL_LIB} #ok
	#v1 : ko
	#SRC_AUX+= ${OPENCV64_VISUAL_LIB}
	#v2 : ok
	ADD_LIBRARY_FILES+= opencv_highgui249.lib  
	ADD_LIBRARY_FILES+= opencv_core249.lib
	ADD_LIBRARY_FILES+= opencv_imgproc249.lib
	
	#runtime
	API_BIN+= ${OPENCV64_VISUAL_BIN}
	
endif

############
# Intel   #
############

ifeq  ($(COMPILATEUR),INTEL)

	#todo
	
	##############
	#Version full
	##############
	
	#compil
	#SRC_AUX+= ${OPENCV64_INC}#ok
	#CXXFLAGS+= -I${OPENCV64_INC} #ko car sous folder

	#link
	#SRC_AUX+= ${OPENCV64_VISUAL_LIB}#ok
	#LDFLAGS+= /LIBPATH:${OPENCV64_VISUAL_LIB} #embettant il faut lister lib now -lxxx
	
	##############
	#Version light 
	##############
	
	#compilation ok
	CXXFLAGS+= -I${OPENCV64_INC}
	CXXFLAGS+= -I${OPENCV64_INC_CV2}
	CXXFLAGS+= -I${OPENCV64_INC_CV2}/highgui
	CXXFLAGS+= -I${OPENCV64_INC_CV2}/core
	CXXFLAGS+= -I${OPENCV64_INC_CV2}/flann
	CXXFLAGS+= -I${OPENCV64_INC_CV2}/imgproc
	CXXFLAGS+= -I${OPENCV64_INC_CV2}/video

	#link ok: 
	LDFLAGS_AUX+=  /LIBPATH:${OPENCV64_VISUAL_LIB} #il faut lister lib now
	#v1 : ko
	#SRC_AUX+= ${OPENCV64_VISUAL_LIB}
	#v2: ok
	ADD_LIBRARY_FILES+= opencv_highgui249.lib 
	ADD_LIBRARY_FILES+= opencv_core249.lib
	ADD_LIBRARY_FILES+= opencv_imgproc249.lib
	
	#runtime
	API_BIN+= ${OPENCV64_VISUAL_BIN}
	
endif

############
# MINGW   #
############

ifeq  ($(COMPILATEUR),MINGW)
	
	#compil : ok
	#SRC_AUX+= ${OPENCV64_INC}#ok
	CXXFLAGS+= -I${OPENCV64_INC}
	CXXFLAGS+= -I${OPENCV64_INC_CV2}
	CXXFLAGS+= -I${OPENCV64_INC_CV2}/highgui
	CXXFLAGS+= -I${OPENCV64_INC_CV2}/core
	CXXFLAGS+= -I${OPENCV64_INC_CV2}/flann
	CXXFLAGS+= -I${OPENCV64_INC_CV2}/imgproc
	CXXFLAGS+= -I${OPENCV64_INC_CV2}/video

	#link : ok
	#SRC_AUX+= ${OPENCV64_MINGW_BIN}#ko
	#LDFLAGS+= -L${OPENCV64_MINGW_LIB_STATIC} #ko existe pas
	LDFLAGS+= -L${OPENCV64_MINGW_LIB} #il faut lister lib now -lxxx
	LDFLAGS+= -lopencv_highgui249 
	LDFLAGS+= -lopencv_core249 
	LDFLAGS+= -lopencv_imgproc249
	
	#runtime
	API_BIN+= ${OPENCV64_MINGW_BIN}
	 
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
	CXXFLAGS+= -I$(subst :, -I,${OPENCV_INC})
	
	#link
	#CXXLDFLAGS+=  -lopencv_highgui -lopencv_core -lopencv_imgproc	 #ko
	#ADD_LIBRARY_FILES+= opencv_highgui   #ok
	#ADD_LIBRARY_FILES+= opencv_core
	#ADD_LIBRARY_FILES+= opencv_imgproc
	
	#LDFLAGS+= -L$(subst :, -L,${OPENCV_LIB})#pas besoin car system
	LDFLAGS+= -l$(subst :, -l,${OPENCV_LIBRARIES}) 

############
# GCC   #
############

ifeq  ($(COMPILATEUR),g++)

	#rien
		
endif

############
# INTEL   #
############

ifeq  ($(COMPILATEUR),INTEL)

	#rien
	
endif

############
# ARM   #
############

ifeq  ($(ARCH),arm)
	LDFLAGS+= -L$(subst :, -L,${OPENCV_LIB})#car use opencv system
	#RPATH_LINK+=${OPENCV_LIB}
endif

endif#end os

##########################################
#   			 END 		   			 #
##########################################

endif#__API_OPEN_CV_MK__

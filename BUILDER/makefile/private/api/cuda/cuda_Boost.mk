# Version 	: 0.0.4
# Author 	: Cedric.Bilat@he-arc.ch
#

ifndef __API_CUDA_BOOST_MK__
__API_CUDA_BOOST_MK__=true

##########################################
#   		Boost Cuda 		   			 #
##########################################


#########################
# 		 WINDOWS		#
#########################

ifeq ($(OS),Win)

############
# Visual   #
############

ifeq ($(COMPILATEUR),VISUAL)

	#include
	NVCCFLAGS+= -I${BOOST64_INC}

	#link
	NVCCLDFLAGS+= -L${BOOST64_VISUAL_LIB_STATIC}
	#NVCCLDFLAGS+= -L${BOOST64_VISUAL_LIB}
	
	
	#runtime
	API_BIN+= ${BOOST64_VISUAL_BIN}
	
endif

endif



#########################
# 		 LINUX			#
#########################

ifeq ($(OS),Linux)

############
# common   #
############

	#instalation : sudo apt-get install libboost-all-dev
	#NVCCFLAGS+= -L/usr/lib  

	#installtion manuel

	#compilation
	#NVCCFLAGS+= -I/opt/boost/include
	NVCCFLAGS+= -I$(subst :, -I,${BOOST_INC})
	
	#link
	#NVCCLDFLAGS+= -L/opt/boost/gcc/lib 
	NVCCLDFLAGS+= -L$(subst :, -L,${BOOST_LIB})
	NVCCLDFLAGS+= -l$(subst :, -l,${BOOST_LIBRARIES}) 
		
	#runtime
	API_BIN+= ${BOOST_LIB}
	
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
	#RPATH_LINK+=${BOOST_LIB}
endif

endif#end os

##########################################
#   			 END 		   			 #
##########################################

endif#__API_CUDA_BOOST_MK__

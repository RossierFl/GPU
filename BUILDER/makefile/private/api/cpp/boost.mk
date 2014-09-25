# Version 	: 0.0.4
# Author 	: Cedric.Bilat@he-arc.ch
#

ifndef __API_BOOST_MK__
__API_BOOST_MK__=true

##########################################
#   			 Boost 		   			 #
##########################################


#########################
# 		 WINDOWS		#
#########################

ifeq ($(OS),Win)

############
# Visual   #
############

ifeq ($(COMPILATEUR),VISUAL)

	#compilation
	CXXFLAGS+= -I${BOOST64_INC}
	
	#link (link static lib)
	LDFLAGS_AUX+=  /LIBPATH:${BOOST64_VISUAL_LIB_STATIC}
	#LDFLAGS_AUX+=  /LIBPATH:${BOOST64_VISUAL_LIB}
	
	#runtime
	#API_BIN+= ${BOOST64_VISUAL_BIN}
endif

############
# Intel   #
############

ifeq  ($(COMPILATEUR),INTEL)

	#compilation
	CXXFLAGS+= -I${BOOST64_INC}

	#link (link static lib)
	LDFLAGS_AUX+= /LIBPATH:${BOOST64_INTEL_LIB_STATIC}
	#LDFLAGS_AUX+= /LIBPATH:${BOOST64_INTEL_LIB}
	
	#runtime
	#API_BIN+= ${BOOST64_INTEL_BIN}
endif

############
# MINGW   #
############

ifeq  ($(COMPILATEUR),MINGW)
	#compilation
  	#CXXFLAGS+= -I${BOOST64_INC} 
  	CXXFLAGS+= -I${BOOST64_MINGW_INC}
  	#-DBOOST_THREAD_USE_LIB

	#link (Link dynamic lib)
	#SRC_AUX+= ${BOOST64_MINGW_LIB}	#ok
	SRC_AUX+= ${BOOST64_MINGW_LIB_STATIC}#ok
	#LDFLAGS+= -L${BOOST64_MINGW_LIB} 
	
	#runtime
	#API_BIN+= ${BOOST64_MINGW_BIN}
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
	#LDFLAGS+= -L/usr/lib  

	#installtion manuel

	#compilation
	CXXFLAGS+= -I$(subst :, -I,${BOOST_INC})

	#link
	#LDFLAGS+= -L/opt/boost/gcc/lib 
	LDFLAGS+= -L$(subst :, -L,${BOOST_LIB})
	LDFLAGS+= -l$(subst :, -l,${BOOST_LIBRARIES}) 
		
	#runtime
	API_BIN+= ${BOOST_LIB}

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
	#RPATH_LINK+=${BOOST_LIB}
endif

endif #end OS

##########################################
#   			 END 		   			 #
##########################################

endif#__API_BOOST_MK__


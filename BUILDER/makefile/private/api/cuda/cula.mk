# Version 	: 0.0.4
# Author 	: Cedric.Bilat@he-arc.ch
#

ifndef __API_CULA_MK__
__API_CULA_MK__=true

##########################################
#   		 Cula 		  	 			 #
##########################################



#########################
# 		 WINDOWS		#
#########################

ifeq ($(OS),Win)

############
# Visual   #
############

ifeq ($(COMPILATEUR),VISUAL)

	#compil
	NVCCFLAGS+= -I${CULA_INC}
	
	#link
	NVCCLDFLAGS+= -L${CULA_LIB}
	NVCCLDFLAGS+= cula_lapack.lib
	
endif

endif

#########################
# 		 LINUX			#
#########################

ifeq ($(OS),Linux)


############
# common   #
############

	#compil
	NVCCFLAGS+= -I$(subst :, -I,${CULA_INC})
	
	#link
	#NVCCLDFLAGS+= -L${CULA_LIB}
	NVCCLDFLAGS+= -L$(subst :, -L,${CULA_LIB})
	NVCCLDFLAGS+= -l$(subst :, -l,${CULA_LIBRARIES}) 

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
	#pas disponible
endif

endif#end os

##########################################
#   			 END 		   			 #
##########################################

endif#__API_CULA_MK__


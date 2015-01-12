# Version 	: 0.0.4
# Author 	: Cedric.Bilat@he-arc.ch
#

ifndef __API_JCUDA_MK__
__API_JCUDA_MK__=true

##########################################
#   		 JCuda 		  	 			 #
##########################################

NVCCFLAGS += -keep -keep-dir ${TARGET_CUBIN}

#########################
# 		 WINDOWS		#
#########################

ifeq ($(OS),Win)

############
# Visual   #
############

ifeq ($(COMPILATEUR),VISUAL)

	# rien
	
endif

endif

#########################
# 		 LINUX			#
#########################

ifeq ($(OS),Linux)

############
# common   #
############

#rien

############
# GCC   #
############

ifeq  ($(COMPILATEUR),g++)

	# rien
	
endif

endif

##########################################
#   			 END 		   			 #
##########################################

endif#__API_JCUDA_MK__


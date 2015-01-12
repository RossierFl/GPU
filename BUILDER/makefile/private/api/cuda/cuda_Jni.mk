# Version 	: 0.0.4
# Author 	: Cedric.Bilat@he-arc.ch
#

ifndef __API_CUDA_JNI_MK__
__API_CUDA_JNI_MK__=true

##########################################
#   			 OpenCV Cuda   			 #
##########################################

include $(API_CUDA)/cuda_Jni_hidden.mk

# Si
#
#	CXXFLAGS += -fvisibility=hidden
#
# Alors methode native ne serait pas visible par java (gcc)
#
# 

NVCCFLAGS_EXCLUDE+= -fvisibility=hidden
#CXXFLAGS_EXCLUDE+= -fvisibility=hidden#

# Maintenant elles sont toutes visibles!

##########################################
#   			 END 		   			 #
##########################################

endif#__API_CUDA_JNI_MK__


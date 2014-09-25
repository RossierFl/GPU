# Version 	: 0.0.4
# Author 	: Cedric.Bilat@he-arc.ch
#

ifndef __API_JNI_MK__
__API_JNI_MK__=true

##########################################
#   		jni				   			 #
##########################################

include $(API)/jni_hidden.mk

# Si
#
#	CXXFLAGS += -fvisibility=hidden
#
# Alors methode native ne serait pas visible par java (gcc,mingw)
#
# 

CXXFLAGS_EXCLUDE+= -fvisibility=hidden#

# Maintenant elles sont toutes visibles!

##########################################
#   			 END 		   			 #
##########################################

endif#__API_JNI_MK__


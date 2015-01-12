# Version 	: 0.0.4
# Author 	: Cedric.Bilat@he-arc.ch
#

ifndef __API_BILAT_DLL_TOOLS_MK__
__API_BILAT_DLL_TOOLS_MK__=true

##########################################
#   		Bilat DLL TOOLS	   			 #
##########################################

#dependance

#compil
SRC_AUX+= ../API_Bilat_DLL_Tools/INC


#########################
# 		 WINDOWS		#
#########################

ifeq ($(OS),Win)

############
# Visual   #
############

ifeq ($(COMPILATEUR),VISUAL)

	#link
	
	
	#runtime
	

endif

############
# Intel   #
############

ifeq  ($(COMPILATEUR),INTEL)

	#link
	
	
	#runtime


endif

############
# MINGW   #
############

ifeq  ($(COMPILATEUR),MINGW)
	
	#link
	
	
	#runtime
	

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
	
	
	#runtime
	

endif

############
# INTEL   #
############

ifeq  ($(COMPILATEUR),INTEL)

	#link
	
	
	#runtime
	

endif

endif

##########################################
#   			 END 		   			 #
##########################################

endif#__API_BILAT_DLL_TOOLS_MK__

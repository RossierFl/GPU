# Version 	: 0.0.6
# Date		: 20.01.2014
# Author 	: Cedric.Bilat@he-arc.ch


ifndef __GCC_ARM_MK__
__GCC_ARM_MK__=true

##############################################
#   			 Variables     				 #
##############################################

########
#arm #
########

ifeq (${ARCH},arm)	

	ARM=true

	# rpath-link : begin
	#
	# Context: 
	#		liba.so depend de libb.so
	#		on link que liba.so avec
	#			-la
	# Probleme:
	#		linker pas content car trouve pas lib.so
	#		warning ou carrement refuse linker!
	#
	# Solution:
	#		Mettre le folder contenant libb.so dans -rpathlink
	#
	# link: 
	#		http://ftp.gnu.org/pub/old-gnu/Manuals/ld-2.9.1/html_node/ld_3.html
	#
	ESPACE:=#
	ESPACE+=#astice de guere
	
	RPATH_LINK:=$(strip ${RPATH_LINK})#replaces each internal sequence of one or more whitespace characters with a single space
	RPATH_LINK:=$(subst ${ESPACE},:,${RPATH_LINK})# ESPACE -> :
	
	ifdef RPATH_LINK 
		RPATH_LINK:=${RPATH_LINK}:/opt/kayla/system/lib#ici pour garantir unicite,si manque warning only, pas error
		RPATH_LINK:= -rpath-link=${RPATH_LINK}#-rpath-link pourrait apparaitre plusieurs fois, 
		override LDFLAGS:= ${RPATH_LINK} ${LDFLAGS}
		override LDFLAGS:= -Xlinker ${LDFLAGS}#-Xlinker doit apparaitre a gauche de -rpath-link. exemple: -Xlinker -rpath-link= 
	endif
	#rpath-link : end
	
	override CXXFLAGS+= ${ARM_CXXFLAGS}
	
endif


#############################################
#       			 END     			    #
#############################################

endif#__GCC_ARM_MK__


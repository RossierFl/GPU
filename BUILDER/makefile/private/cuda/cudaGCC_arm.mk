# Version 	: 0.0.6
# Date		: 20.01.2014
# Author 	: Cedric.Bilat@he-arc.ch

ifndef __CUDA_GCC_ARM_MK__
__CUDA_GCC_ARM_MK__=true

##############################################
#   			 Variables     				 #
##############################################

########
#arm #
########

ifeq (${ARCH},arm)	

	ARM=true

	#rpath-link : begin
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
	ESPACE+=#astuce de guere
	
	RPATH_LINK:=$(strip ${RPATH_LINK})#replaces each internal sequence of one or more whitespace characters with a single space
	RPATH_LINK:=$(subst ${ESPACE},:,${RPATH_LINK})# ESPACE -> :

	ifdef RPATH_LINK 
		RPATH_LINK:=${RPATH_LINK}:/opt/kayla/system/lib#ici pour garantir unicite, si manque warning only, pas error
		RPATH_LINK:= -rpath-link=${RPATH_LINK}#-rpath-link pourrait apparaitre plusieurs fois
		override CXXLDFLAGS:= ${RPATH_LINK} ${CXXLDFLAGS}
	endif
	#rpath-link : end
	
	override ARMFLAGS:= -ccbin g++ARM ${ARMFLAGS}
	override ARMFLAGS:= -m32 ${ARMFLAGS}
	override ARMFLAGS:= -target-cpu-arch ARM ${ARMFLAGS}
	
	override NVCCFLAGS:= ${ARMFLAGS} ${NVCCFLAGS}
	override NVCCLDFLAGS:= ${ARMFLAGS} ${NVCCLDFLAGS}
		 
	override NVCCFLAGS_EXCLUDE+= -m64#
	 
	override CXXFLAGS+= ${ARM_CXXFLAGS}

else
	
	ifeq (${DEBUG},false)	 
		override CXXFLAGS+= ${X86_CXX_OPTIMISATION}
	endif
	
endif

ifeq (${DEBUG},false)	
	override CXXFLAGS+= ${CXX_OPTIMISATION}
endif

#####################
# 		Target 		#
#####################

KAYLA_IP=157.26.103.143
JETSON_IP=157.26.100.60

KAYLA_USER=ubuntu
JETSON_USER=ubuntu

KAYLA_BIN=/home/ubuntu/bin
JETSON_BIN=/home/ubuntu/bin

########
# Copy #
########

.PHONY: toKayla	
toKayla:
	@echo ""
	@echo "[CBI] -> Copy to Kayla ${KAYLA_IP}: "$(TARGET_DEPLOY)
	@echo scp $(TARGET_DEPLOY) ${KAYLA_USER}@${KAYLA_IP}:${KAYLA_BIN}
	@scp $(TARGET_DEPLOY) ${KAYLA_USER}@${KAYLA_IP}:${KAYLA_BIN}
	@echo "[CBI] -> ..."
	@echo "[CBI] -> Sucess!"
	@echo ""

.PHONY: toJetson
toJetson:
	@echo ""
	@echo "[CBI] -> Copy to Jetson ${JETSON_IP}: "$(TARGET_DEPLOY)
	@echo scp $(TARGET_DEPLOY) ${JETSON_USER}@${JETSON_IP}:${JETSON_BIN}
	@scp $(TARGET_DEPLOY) ${JETSON_USER}@${JETSON_IP}:${JETSON_BIN}
	@echo "[CBI] -> ..."
	@echo "[CBI] -> Sucess!"
	@echo ""

########
# execute #
########

.PHONY: runKayla	
runKayla:
	@echo ""
	@echo "[CBI] -> Run on Kayla: $(TARGET_NAME).run"
	@echo ""
	@echo "[CBI] -> ssh -X ${KAYLA_USER}@${KAYLA_IP} cbirt ${KAYLA_BIN}/$(TARGET_NAME).run"
	@echo ""
	@ssh ${KAYLA_USER}@${KAYLA_IP} cbirt ${KAYLA_BIN}/$(TARGET_NAME).run
	@echo ""

.PHONY: runKaylaGL	
runKaylaGL:
	@echo ""
	@echo "[CBI] -> Run on Kayla [GL]: $(TARGET_NAME).run"
	@echo ""
	@echo "[CBI] -> ssh -X ${KAYLA_USER}@${KAYLA_IP} cbirt ${KAYLA_BIN}/$(TARGET_NAME).run"
	@echo ""
	@ssh -X ${KAYLA_USER}@${KAYLA_IP} cbirt ${KAYLA_BIN}/$(TARGET_NAME).run
	@echo ""
	#ko avec GL error while loading shared libraries: libcudart.so.5.0 why?

	
.PHONY: runJetson	
runJetson:
	@echo ""
	@echo "[CBI] -> Run on Jetson: $(TARGET_NAME).run"
	@echo ""
	@echo "[CBI] -> ssh -X ${JETSON_USER}@${JETSON_IP} cbirt ${JETSON_BIN}/$(TARGET_NAME).run"
	@echo ""
	@ssh ${JETSON_USER}@${JETSON_IP} cbirt ${JETSON_BIN}/$(TARGET_NAME).run
	@echo ""
	
.PHONY: runJetsonGL	
runJetsonGL:
	@echo ""
	@echo "[CBI] -> Run on Jetson [GL]: $(TARGET_NAME).run"
	@echo ""
	@echo "[CBI] -> ssh -X ${JETSON_USER}@${JETSON_IP} cbirt ${JETSON_BIN}/$(TARGET_NAME).run"
	@echo ""
	@ssh -X ${JETSON_USER}@${JETSON_IP} cbirt ${JETSON_BIN}/$(TARGET_NAME).run
	@echo ""
	#ko avec GL error while loading shared libraries: libcudart.so.5.0 why?
	
#############################################
#       			 END     			    #
#############################################

endif#__OCUDA_GCC_ARM_MK__


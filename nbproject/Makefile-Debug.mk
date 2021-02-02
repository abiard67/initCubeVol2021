#
# Generated Makefile - do not edit!
#
# Edit the Makefile in the project folder instead (../Makefile). Each target
# has a -pre and a -post target defined where you can add customized code.
#
# This makefile implements configuration specific macros and targets.


# Environment
MKDIR=mkdir
CP=cp
GREP=grep
NM=nm
CCADMIN=CCadmin
RANLIB=ranlib
CC=gcc
CCC=c++
CXX=c++
FC=gfortran
AS=as

# Macros
CND_PLATFORM=GNU-Linux
CND_DLIB_EXT=so
CND_CONF=Debug
CND_DISTDIR=dist
CND_BUILDDIR=build

# Include project Makefile
include initCubeVol2021-Makefile.mk

# Object Directory
OBJECTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/src/Batterie.o \
	${OBJECTDIR}/src/CameraIR.o \
	${OBJECTDIR}/src/Commande.o \
	${OBJECTDIR}/src/EmetteurRecepteur.o \
	${OBJECTDIR}/src/Etat.o \
	${OBJECTDIR}/src/Horloge.o \
	${OBJECTDIR}/src/I2C.o \
	${OBJECTDIR}/src/Instrument.o \
	${OBJECTDIR}/src/Message.o \
	${OBJECTDIR}/src/Mesure.o \
	${OBJECTDIR}/src/Mission.o \
	${OBJECTDIR}/src/Ordinateur.o \
	${OBJECTDIR}/src/Protocole.o \
	${OBJECTDIR}/src/Reboot.o \
	${OBJECTDIR}/src/Sauvegarde.o \
	${OBJECTDIR}/src/SegmentSol.o \
	${OBJECTDIR}/src/SegmentVol.o \
	${OBJECTDIR}/src/Status.o \
	${OBJECTDIR}/src/Stockage.o \
	${OBJECTDIR}/src/Temperature.o \
	${OBJECTDIR}/src/TypeAck.o \
	${OBJECTDIR}/src/TypeAppareil.o \
	${OBJECTDIR}/src/TypeCommande.o \
	${OBJECTDIR}/src/TypeMisEtat.o \
	${OBJECTDIR}/src/main.o \
	${OBJECTDIR}/src/serialib.o


# C Compiler Flags
CFLAGS=

# CC Compiler Flags
CCFLAGS=
CXXFLAGS=

# Fortran Compiler Flags
FFLAGS=

# Assembler Flags
ASFLAGS=

# Link Libraries and Options
LDLIBSOPTIONS=

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/initcubevol2021

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/initcubevol2021: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.cc} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/initcubevol2021 ${OBJECTFILES} ${LDLIBSOPTIONS}

${OBJECTDIR}/src/Batterie.o: src/Batterie.cpp
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} "$@.d"
	$(COMPILE.cc) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/Batterie.o src/Batterie.cpp

${OBJECTDIR}/src/CameraIR.o: src/CameraIR.cpp
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} "$@.d"
	$(COMPILE.cc) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/CameraIR.o src/CameraIR.cpp

${OBJECTDIR}/src/Commande.o: src/Commande.cpp
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} "$@.d"
	$(COMPILE.cc) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/Commande.o src/Commande.cpp

${OBJECTDIR}/src/EmetteurRecepteur.o: src/EmetteurRecepteur.cpp
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} "$@.d"
	$(COMPILE.cc) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/EmetteurRecepteur.o src/EmetteurRecepteur.cpp

${OBJECTDIR}/src/Etat.o: src/Etat.cpp
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} "$@.d"
	$(COMPILE.cc) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/Etat.o src/Etat.cpp

${OBJECTDIR}/src/Horloge.o: src/Horloge.cpp
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} "$@.d"
	$(COMPILE.cc) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/Horloge.o src/Horloge.cpp

${OBJECTDIR}/src/I2C.o: src/I2C.cpp
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} "$@.d"
	$(COMPILE.cc) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/I2C.o src/I2C.cpp

${OBJECTDIR}/src/Instrument.o: src/Instrument.cpp
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} "$@.d"
	$(COMPILE.cc) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/Instrument.o src/Instrument.cpp

${OBJECTDIR}/src/Message.o: src/Message.cpp
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} "$@.d"
	$(COMPILE.cc) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/Message.o src/Message.cpp

${OBJECTDIR}/src/Mesure.o: src/Mesure.cpp
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} "$@.d"
	$(COMPILE.cc) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/Mesure.o src/Mesure.cpp

${OBJECTDIR}/src/Mission.o: src/Mission.cpp
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} "$@.d"
	$(COMPILE.cc) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/Mission.o src/Mission.cpp

${OBJECTDIR}/src/Ordinateur.o: src/Ordinateur.cpp
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} "$@.d"
	$(COMPILE.cc) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/Ordinateur.o src/Ordinateur.cpp

${OBJECTDIR}/src/Protocole.o: src/Protocole.cpp
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} "$@.d"
	$(COMPILE.cc) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/Protocole.o src/Protocole.cpp

${OBJECTDIR}/src/Reboot.o: src/Reboot.cpp
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} "$@.d"
	$(COMPILE.cc) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/Reboot.o src/Reboot.cpp

${OBJECTDIR}/src/Sauvegarde.o: src/Sauvegarde.cpp
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} "$@.d"
	$(COMPILE.cc) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/Sauvegarde.o src/Sauvegarde.cpp

${OBJECTDIR}/src/SegmentSol.o: src/SegmentSol.cpp
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} "$@.d"
	$(COMPILE.cc) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/SegmentSol.o src/SegmentSol.cpp

${OBJECTDIR}/src/SegmentVol.o: src/SegmentVol.cpp
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} "$@.d"
	$(COMPILE.cc) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/SegmentVol.o src/SegmentVol.cpp

${OBJECTDIR}/src/Status.o: src/Status.cpp
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} "$@.d"
	$(COMPILE.cc) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/Status.o src/Status.cpp

${OBJECTDIR}/src/Stockage.o: src/Stockage.cpp
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} "$@.d"
	$(COMPILE.cc) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/Stockage.o src/Stockage.cpp

${OBJECTDIR}/src/Temperature.o: src/Temperature.cpp
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} "$@.d"
	$(COMPILE.cc) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/Temperature.o src/Temperature.cpp

${OBJECTDIR}/src/TypeAck.o: src/TypeAck.cpp
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} "$@.d"
	$(COMPILE.cc) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/TypeAck.o src/TypeAck.cpp

${OBJECTDIR}/src/TypeAppareil.o: src/TypeAppareil.cpp
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} "$@.d"
	$(COMPILE.cc) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/TypeAppareil.o src/TypeAppareil.cpp

${OBJECTDIR}/src/TypeCommande.o: src/TypeCommande.cpp
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} "$@.d"
	$(COMPILE.cc) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/TypeCommande.o src/TypeCommande.cpp

${OBJECTDIR}/src/TypeMisEtat.o: src/TypeMisEtat.cpp
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} "$@.d"
	$(COMPILE.cc) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/TypeMisEtat.o src/TypeMisEtat.cpp

${OBJECTDIR}/src/main.o: src/main.cpp
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} "$@.d"
	$(COMPILE.cc) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/main.o src/main.cpp

${OBJECTDIR}/src/serialib.o: src/serialib.cpp
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} "$@.d"
	$(COMPILE.cc) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/serialib.o src/serialib.cpp

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc

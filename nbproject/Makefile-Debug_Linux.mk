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
CCC=g++
CXX=g++
FC=gfortran
AS=as

# Macros
CND_PLATFORM=GNU-Linux-x86
CND_CONF=Debug_Linux
CND_DISTDIR=dist
CND_BUILDDIR=build

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/Stats.o \
	${OBJECTDIR}/RRD.o \
	${OBJECTDIR}/PacketAnalyzer.o \
	${OBJECTDIR}/main.o \
	${OBJECTDIR}/RRDUpdater.o \
	${OBJECTDIR}/config.o \
	${OBJECTDIR}/PacketLogger.o \
	${OBJECTDIR}/StatsAdapter.o \
	${OBJECTDIR}/netstruct.o


# C Compiler Flags
CFLAGS=

# CC Compiler Flags
CCFLAGS=-std=c++0x
CXXFLAGS=-std=c++0x

# Fortran Compiler Flags
FFLAGS=

# Assembler Flags
ASFLAGS=

# Link Libraries and Options
LDLIBSOPTIONS=-lrrd -lpcap

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/pcaprrd

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/pcaprrd: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.cc} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/pcaprrd ${OBJECTFILES} ${LDLIBSOPTIONS} 

${OBJECTDIR}/Stats.o: Stats.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g -Wall -DLINUX -DDEBUG -MMD -MP -MF $@.d -o ${OBJECTDIR}/Stats.o Stats.cpp

${OBJECTDIR}/RRD.o: RRD.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g -Wall -DLINUX -DDEBUG -MMD -MP -MF $@.d -o ${OBJECTDIR}/RRD.o RRD.cpp

${OBJECTDIR}/PacketAnalyzer.o: PacketAnalyzer.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g -Wall -DLINUX -DDEBUG -MMD -MP -MF $@.d -o ${OBJECTDIR}/PacketAnalyzer.o PacketAnalyzer.cpp

${OBJECTDIR}/main.o: main.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g -Wall -DLINUX -DDEBUG -MMD -MP -MF $@.d -o ${OBJECTDIR}/main.o main.cpp

${OBJECTDIR}/RRDUpdater.o: RRDUpdater.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g -Wall -DLINUX -DDEBUG -MMD -MP -MF $@.d -o ${OBJECTDIR}/RRDUpdater.o RRDUpdater.cpp

${OBJECTDIR}/config.o: config.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g -Wall -DLINUX -DDEBUG -MMD -MP -MF $@.d -o ${OBJECTDIR}/config.o config.cpp

${OBJECTDIR}/PacketLogger.o: PacketLogger.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g -Wall -DLINUX -DDEBUG -MMD -MP -MF $@.d -o ${OBJECTDIR}/PacketLogger.o PacketLogger.cpp

${OBJECTDIR}/StatsAdapter.o: StatsAdapter.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g -Wall -DLINUX -DDEBUG -MMD -MP -MF $@.d -o ${OBJECTDIR}/StatsAdapter.o StatsAdapter.cpp

${OBJECTDIR}/netstruct.o: netstruct.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g -Wall -DLINUX -DDEBUG -MMD -MP -MF $@.d -o ${OBJECTDIR}/netstruct.o netstruct.cpp

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}
	${RM} ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/pcaprrd

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc

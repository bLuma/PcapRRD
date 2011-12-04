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
CC=gcc.exe
CCC=g++.exe
CXX=g++.exe
FC=gfortran
AS=as.exe

# Macros
CND_PLATFORM=Cygwin-Windows
CND_CONF=Release
CND_DISTDIR=dist
CND_BUILDDIR=build

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/src/main.o \
	${OBJECTDIR}/src/StatsAdapter.o \
	${OBJECTDIR}/src/Config.o \
	${OBJECTDIR}/src/PacketLogger.o \
	${OBJECTDIR}/src/Stats.o \
	${OBJECTDIR}/src/netstruct.o \
	${OBJECTDIR}/src/PacketAnalyzer.o \
	${OBJECTDIR}/src/RRD.o \
	${OBJECTDIR}/src/RRDUpdater.o


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
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/pcaprrd.exe

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/pcaprrd.exe: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.cc} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/pcaprrd ${OBJECTFILES} ${LDLIBSOPTIONS} 

${OBJECTDIR}/src/main.o: src/main.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -O2 -DDEBUG -DWIN -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/main.o src/main.cpp

${OBJECTDIR}/src/StatsAdapter.o: src/StatsAdapter.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -O2 -DDEBUG -DWIN -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/StatsAdapter.o src/StatsAdapter.cpp

${OBJECTDIR}/src/Config.o: src/Config.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -O2 -DDEBUG -DWIN -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/Config.o src/Config.cpp

${OBJECTDIR}/src/PacketLogger.o: src/PacketLogger.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -O2 -DDEBUG -DWIN -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/PacketLogger.o src/PacketLogger.cpp

${OBJECTDIR}/src/Stats.o: src/Stats.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -O2 -DDEBUG -DWIN -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/Stats.o src/Stats.cpp

${OBJECTDIR}/src/netstruct.o: src/netstruct.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -O2 -DDEBUG -DWIN -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/netstruct.o src/netstruct.cpp

${OBJECTDIR}/src/PacketAnalyzer.o: src/PacketAnalyzer.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -O2 -DDEBUG -DWIN -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/PacketAnalyzer.o src/PacketAnalyzer.cpp

${OBJECTDIR}/src/RRD.o: src/RRD.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -O2 -DDEBUG -DWIN -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/RRD.o src/RRD.cpp

${OBJECTDIR}/src/RRDUpdater.o: src/RRDUpdater.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -O2 -DDEBUG -DWIN -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/RRDUpdater.o src/RRDUpdater.cpp

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}
	${RM} ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/pcaprrd.exe

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc

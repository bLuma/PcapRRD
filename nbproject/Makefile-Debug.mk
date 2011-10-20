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
CND_CONF=Debug
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
	${OBJECTDIR}/PacketLogger.o


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
LDLIBSOPTIONS=-L../winpcap/Lib -lpacket -lwpcap

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/pcaprrd.exe

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/pcaprrd.exe: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.cc} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/pcaprrd ${OBJECTFILES} ${LDLIBSOPTIONS} 

${OBJECTDIR}/Stats.o: Stats.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g -Wall -DDEBUG -DWIN -I../winpcap/Include -I../rrdtool.src/src -MMD -MP -MF $@.d -o ${OBJECTDIR}/Stats.o Stats.cpp

${OBJECTDIR}/RRD.o: RRD.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g -Wall -DDEBUG -DWIN -I../winpcap/Include -I../rrdtool.src/src -MMD -MP -MF $@.d -o ${OBJECTDIR}/RRD.o RRD.cpp

${OBJECTDIR}/PacketAnalyzer.o: PacketAnalyzer.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g -Wall -DDEBUG -DWIN -I../winpcap/Include -I../rrdtool.src/src -MMD -MP -MF $@.d -o ${OBJECTDIR}/PacketAnalyzer.o PacketAnalyzer.cpp

${OBJECTDIR}/main.o: main.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g -Wall -DDEBUG -DWIN -I../winpcap/Include -I../rrdtool.src/src -MMD -MP -MF $@.d -o ${OBJECTDIR}/main.o main.cpp

${OBJECTDIR}/PacketLogger.o: PacketLogger.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g -Wall -DDEBUG -DWIN -I../winpcap/Include -I../rrdtool.src/src -MMD -MP -MF $@.d -o ${OBJECTDIR}/PacketLogger.o PacketLogger.cpp

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

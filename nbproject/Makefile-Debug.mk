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
CND_PLATFORM=GNU-Linux
CND_DLIB_EXT=so
CND_CONF=Debug
CND_DISTDIR=dist
CND_BUILDDIR=build

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/keyboard.o \
	${OBJECTDIR}/mouse.o


# C Compiler Flags
CFLAGS=-m64 -lX11 -lXtst

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
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libnativeioaccess.${CND_DLIB_EXT}

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libnativeioaccess.${CND_DLIB_EXT}: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.c} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libnativeioaccess.${CND_DLIB_EXT} ${OBJECTFILES} ${LDLIBSOPTIONS} -shared -fPIC

${OBJECTDIR}/keyboard.o: keyboard.c
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.c) -g -I/opt/jdk1.8.0_141/include -I/opt/jdk1.8.0_141/include/linux -I/opt/jdk1.8.0_141/include/main -I/usr/include/X11/extensions -include /opt/jdk1.8.0_151/include/jawt.h -include /opt/jdk1.8.0_151/include/jni.h -include ../../headers/ameliaclient_nativesupport_NativeKeyboardController.h -include ../../headers/ameliaclient_nativesupport_NativeMouseController.h -include /opt/jdk1.8.0_151/include/linux/jni_md.h -std=c11 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/keyboard.o keyboard.c

${OBJECTDIR}/mouse.o: mouse.c
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.c) -g -I/opt/jdk1.8.0_141/include -I/opt/jdk1.8.0_141/include/linux -I/opt/jdk1.8.0_141/include/main -I/usr/include/X11/extensions -include /opt/jdk1.8.0_151/include/jawt.h -include /opt/jdk1.8.0_151/include/jni.h -include ../../headers/ameliaclient_nativesupport_NativeKeyboardController.h -include ../../headers/ameliaclient_nativesupport_NativeMouseController.h -include /opt/jdk1.8.0_151/include/linux/jni_md.h -std=c11 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/mouse.o mouse.c

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

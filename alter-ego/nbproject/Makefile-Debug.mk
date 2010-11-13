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
CCADMIN=CCadmin
RANLIB=ranlib
CC=gcc
CCC=g++
CXX=g++
FC=
AS=as

# Macros
CND_PLATFORM=GNU-Linux-x86
CND_CONF=Debug
CND_DISTDIR=dist

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=build/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/src/alter_ego.o

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
LDLIBSOPTIONS=../imago_c/dist/Debug/GNU-Linux-x86/libimago_c.a ../imago/dist/Debug/GNU-Linux-x86/libimago.a -lpthread

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	${MAKE}  -f nbproject/Makefile-Debug.mk dist/Debug/GNU-Linux-x86/alter-ego

dist/Debug/GNU-Linux-x86/alter-ego: ../imago_c/dist/Debug/GNU-Linux-x86/libimago_c.a

dist/Debug/GNU-Linux-x86/alter-ego: ../imago/dist/Debug/GNU-Linux-x86/libimago.a

dist/Debug/GNU-Linux-x86/alter-ego: ${OBJECTFILES}
	${MKDIR} -p dist/Debug/GNU-Linux-x86
	${LINK.cc} -lpng -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/alter-ego ${OBJECTFILES} ${LDLIBSOPTIONS} 

${OBJECTDIR}/src/alter_ego.o: nbproject/Makefile-${CND_CONF}.mk src/alter_ego.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -g -I../imago_c/src -I.. -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/alter_ego.o src/alter_ego.cpp

# Subprojects
.build-subprojects:
	cd ../imago_c && ${MAKE}  -f Makefile CONF=Debug
	cd ../imago && ${MAKE}  -f Makefile CONF=Debug

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r build/Debug
	${RM} dist/Debug/GNU-Linux-x86/alter-ego

# Subprojects
.clean-subprojects:
	cd ../imago_c && ${MAKE}  -f Makefile CONF=Debug clean
	cd ../imago && ${MAKE}  -f Makefile CONF=Debug clean

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc

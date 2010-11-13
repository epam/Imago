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
	${OBJECTDIR}/src/molecule.o \
	${OBJECTDIR}/src/rectangle.o \
	${OBJECTDIR}/src/thin_filter2.o \
	${OBJECTDIR}/src/label_combiner.o \
	${OBJECTDIR}/src/double_bond_maker.o \
	${OBJECTDIR}/src/wedge_bond_extractor.o \
	${OBJECTDIR}/src/log.o \
	${OBJECTDIR}/src/approximator.o \
	${OBJECTDIR}/src/scanner.o \
	${OBJECTDIR}/src/image_utils.o \
	${OBJECTDIR}/src/binarizer.o \
	${OBJECTDIR}/src/chemical_structure_recognizer.o \
	${OBJECTDIR}/src/segment.o \
	${OBJECTDIR}/src/triple_bond_maker.o \
	${OBJECTDIR}/src/image.o \
	${OBJECTDIR}/src/image_draw_utils.o \
	${OBJECTDIR}/src/filter.o \
	${OBJECTDIR}/src/segmentator.o \
	${OBJECTDIR}/src/static_object.o \
	${OBJECTDIR}/src/algebra.o \
	${OBJECTDIR}/src/graph_extractor.o \
	${OBJECTDIR}/src/lock_posix.o \
	${OBJECTDIR}/src/png_saver.o \
	${OBJECTDIR}/src/recognition_settings.o \
	${OBJECTDIR}/src/skeleton.o \
	${OBJECTDIR}/src/vec2d.o \
	${OBJECTDIR}/src/font.o \
	${OBJECTDIR}/src/png_loader.o \
	${OBJECTDIR}/src/convolver.o \
	${OBJECTDIR}/src/fourier_descriptors_extractor.o \
	${OBJECTDIR}/src/separator.o \
	${OBJECTDIR}/src/graphics_detector.o \
	${OBJECTDIR}/src/session_manager.o \
	${OBJECTDIR}/src/molfile_saver.o \
	${OBJECTDIR}/src/exception.o \
	${OBJECTDIR}/src/output.o \
	${OBJECTDIR}/src/label_logic.o \
	${OBJECTDIR}/src/segments_graph.o \
	${OBJECTDIR}/src/thread_local_posix.o

# C Compiler Flags
CFLAGS=

# CC Compiler Flags
CCFLAGS=-fPIC
CXXFLAGS=-fPIC

# Fortran Compiler Flags
FFLAGS=

# Assembler Flags
ASFLAGS=

# Link Libraries and Options
LDLIBSOPTIONS=

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	${MAKE}  -f nbproject/Makefile-Debug.mk dist/Debug/GNU-Linux-x86/libimago.a

dist/Debug/GNU-Linux-x86/libimago.a: ${OBJECTFILES}
	${MKDIR} -p dist/Debug/GNU-Linux-x86
	${RM} dist/Debug/GNU-Linux-x86/libimago.a
	${AR} rv ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libimago.a ${OBJECTFILES} 
	$(RANLIB) dist/Debug/GNU-Linux-x86/libimago.a

${OBJECTDIR}/src/molecule.o: nbproject/Makefile-${CND_CONF}.mk src/molecule.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -g -Wall -I.. -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/molecule.o src/molecule.cpp

${OBJECTDIR}/src/rectangle.o: nbproject/Makefile-${CND_CONF}.mk src/rectangle.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -g -Wall -I.. -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/rectangle.o src/rectangle.cpp

${OBJECTDIR}/src/thin_filter2.o: nbproject/Makefile-${CND_CONF}.mk src/thin_filter2.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -g -Wall -I.. -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/thin_filter2.o src/thin_filter2.cpp

${OBJECTDIR}/src/label_combiner.o: nbproject/Makefile-${CND_CONF}.mk src/label_combiner.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -g -Wall -I.. -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/label_combiner.o src/label_combiner.cpp

${OBJECTDIR}/src/double_bond_maker.o: nbproject/Makefile-${CND_CONF}.mk src/double_bond_maker.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -g -Wall -I.. -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/double_bond_maker.o src/double_bond_maker.cpp

${OBJECTDIR}/src/wedge_bond_extractor.o: nbproject/Makefile-${CND_CONF}.mk src/wedge_bond_extractor.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -g -Wall -I.. -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/wedge_bond_extractor.o src/wedge_bond_extractor.cpp

${OBJECTDIR}/src/log.o: nbproject/Makefile-${CND_CONF}.mk src/log.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -g -Wall -I.. -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/log.o src/log.cpp

${OBJECTDIR}/src/approximator.o: nbproject/Makefile-${CND_CONF}.mk src/approximator.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -g -Wall -I.. -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/approximator.o src/approximator.cpp

${OBJECTDIR}/src/scanner.o: nbproject/Makefile-${CND_CONF}.mk src/scanner.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -g -Wall -I.. -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/scanner.o src/scanner.cpp

${OBJECTDIR}/src/image_utils.o: nbproject/Makefile-${CND_CONF}.mk src/image_utils.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -g -Wall -I.. -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/image_utils.o src/image_utils.cpp

${OBJECTDIR}/src/binarizer.o: nbproject/Makefile-${CND_CONF}.mk src/binarizer.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -g -Wall -I.. -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/binarizer.o src/binarizer.cpp

${OBJECTDIR}/src/chemical_structure_recognizer.o: nbproject/Makefile-${CND_CONF}.mk src/chemical_structure_recognizer.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -g -Wall -I.. -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/chemical_structure_recognizer.o src/chemical_structure_recognizer.cpp

${OBJECTDIR}/src/segment.o: nbproject/Makefile-${CND_CONF}.mk src/segment.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -g -Wall -I.. -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/segment.o src/segment.cpp

${OBJECTDIR}/src/triple_bond_maker.o: nbproject/Makefile-${CND_CONF}.mk src/triple_bond_maker.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -g -Wall -I.. -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/triple_bond_maker.o src/triple_bond_maker.cpp

${OBJECTDIR}/src/image.o: nbproject/Makefile-${CND_CONF}.mk src/image.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -g -Wall -I.. -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/image.o src/image.cpp

${OBJECTDIR}/src/image_draw_utils.o: nbproject/Makefile-${CND_CONF}.mk src/image_draw_utils.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -g -Wall -I.. -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/image_draw_utils.o src/image_draw_utils.cpp

${OBJECTDIR}/src/filter.o: nbproject/Makefile-${CND_CONF}.mk src/filter.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -g -Wall -I.. -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/filter.o src/filter.cpp

${OBJECTDIR}/src/segmentator.o: nbproject/Makefile-${CND_CONF}.mk src/segmentator.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -g -Wall -I.. -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/segmentator.o src/segmentator.cpp

${OBJECTDIR}/src/static_object.o: nbproject/Makefile-${CND_CONF}.mk src/static_object.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -g -Wall -I.. -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/static_object.o src/static_object.cpp

${OBJECTDIR}/src/algebra.o: nbproject/Makefile-${CND_CONF}.mk src/algebra.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -g -Wall -I.. -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/algebra.o src/algebra.cpp

${OBJECTDIR}/src/graph_extractor.o: nbproject/Makefile-${CND_CONF}.mk src/graph_extractor.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -g -Wall -I.. -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/graph_extractor.o src/graph_extractor.cpp

${OBJECTDIR}/src/lock_posix.o: nbproject/Makefile-${CND_CONF}.mk src/lock_posix.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -g -Wall -I.. -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/lock_posix.o src/lock_posix.cpp

${OBJECTDIR}/src/png_saver.o: nbproject/Makefile-${CND_CONF}.mk src/png_saver.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -g -Wall -I.. -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/png_saver.o src/png_saver.cpp

${OBJECTDIR}/src/recognition_settings.o: nbproject/Makefile-${CND_CONF}.mk src/recognition_settings.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -g -Wall -I.. -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/recognition_settings.o src/recognition_settings.cpp

${OBJECTDIR}/src/skeleton.o: nbproject/Makefile-${CND_CONF}.mk src/skeleton.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -g -Wall -I.. -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/skeleton.o src/skeleton.cpp

${OBJECTDIR}/src/vec2d.o: nbproject/Makefile-${CND_CONF}.mk src/vec2d.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -g -Wall -I.. -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/vec2d.o src/vec2d.cpp

${OBJECTDIR}/src/font.o: nbproject/Makefile-${CND_CONF}.mk src/font.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -g -Wall -I.. -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/font.o src/font.cpp

${OBJECTDIR}/src/png_loader.o: nbproject/Makefile-${CND_CONF}.mk src/png_loader.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -g -Wall -I.. -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/png_loader.o src/png_loader.cpp

${OBJECTDIR}/src/convolver.o: nbproject/Makefile-${CND_CONF}.mk src/convolver.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -g -Wall -I.. -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/convolver.o src/convolver.cpp

${OBJECTDIR}/src/fourier_descriptors_extractor.o: nbproject/Makefile-${CND_CONF}.mk src/fourier_descriptors_extractor.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -g -Wall -I.. -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/fourier_descriptors_extractor.o src/fourier_descriptors_extractor.cpp

${OBJECTDIR}/src/separator.o: nbproject/Makefile-${CND_CONF}.mk src/separator.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -g -Wall -I.. -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/separator.o src/separator.cpp

${OBJECTDIR}/src/graphics_detector.o: nbproject/Makefile-${CND_CONF}.mk src/graphics_detector.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -g -Wall -I.. -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/graphics_detector.o src/graphics_detector.cpp

${OBJECTDIR}/src/session_manager.o: nbproject/Makefile-${CND_CONF}.mk src/session_manager.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -g -Wall -I.. -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/session_manager.o src/session_manager.cpp

${OBJECTDIR}/src/molfile_saver.o: nbproject/Makefile-${CND_CONF}.mk src/molfile_saver.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -g -Wall -I.. -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/molfile_saver.o src/molfile_saver.cpp

${OBJECTDIR}/src/exception.o: nbproject/Makefile-${CND_CONF}.mk src/exception.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -g -Wall -I.. -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/exception.o src/exception.cpp

${OBJECTDIR}/src/output.o: nbproject/Makefile-${CND_CONF}.mk src/output.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -g -Wall -I.. -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/output.o src/output.cpp

${OBJECTDIR}/src/label_logic.o: nbproject/Makefile-${CND_CONF}.mk src/label_logic.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -g -Wall -I.. -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/label_logic.o src/label_logic.cpp

${OBJECTDIR}/src/segments_graph.o: nbproject/Makefile-${CND_CONF}.mk src/segments_graph.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -g -Wall -I.. -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/segments_graph.o src/segments_graph.cpp

${OBJECTDIR}/src/thread_local_posix.o: nbproject/Makefile-${CND_CONF}.mk src/thread_local_posix.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -g -Wall -I.. -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/thread_local_posix.o src/thread_local_posix.cpp

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r build/Debug
	${RM} dist/Debug/GNU-Linux-x86/libimago.a

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc

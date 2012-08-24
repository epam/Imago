option(IMAGO_BITNESS "Target bitness" 64)
if(${IMAGO_BITNESS} EQUAL 64)
   	set(SUBSYSTEM_NAME "x64")
elseif(${IMAGO_BITNESS} EQUAL 32)
	set(SUBSYSTEM_NAME "x86")
endif()

find_package(Threads REQUIRED)
if(${SUBSYSTEM_NAME} STREQUAL "x86")	
	set(IMAGO_C_FLAGS "-m32")
	set(INDIGO_LIBS_DIR "${INDIGO_LIBS_DIR}/linux32")
	set(OpenCV_DIR "${OpenCV_DIR}/linux32/share/OpenCV")
	set(BOOST_LIBRARYDIR "${BOOST_LIBRARYDIR}/linux32")
elseif(${SUBSYSTEM_NAME} STREQUAL "x64")
	set(IMAGO_C_FLAGS "-m64")
	set(INDIGO_LIBS_DIR "${INDIGO_LIBS_DIR}/linux64")
	set(OpenCV_DIR "${OpenCV_DIR}/linux64/share/OpenCV")
	set(BOOST_LIBRARYDIR "${BOOST_LIBRARYDIR}/linux64")
else()
	message(FATAL_ERROR "Wrong bitness!")
endif()

set(INDIGO_LIBS 
	${INDIGO_LIBS_DIR}/libindigo-static.a
	${INDIGO_LIBS_DIR}/libcommon.a 
	${INDIGO_LIBS_DIR}/libmolecule.a  
	${INDIGO_LIBS_DIR}/libreaction.a
	${INDIGO_LIBS_DIR}/liblayout.a 
	${INDIGO_LIBS_DIR}/libz.a 
	${INDIGO_LIBS_DIR}/libtinyxml.a 
	${INDIGO_LIBS_DIR}/libcommon.a 
	${INDIGO_LIBS_DIR}/libmolecule.a  
	${INDIGO_LIBS_DIR}/libgraph.a)

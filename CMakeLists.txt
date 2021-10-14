cmake_minimum_required(VERSION 3.0)

project("Imago")

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_CURRENT_SOURCE_DIR}/cmake/)
set(CMAKE_INSTALL_PREFIX ${CMAKE_CURRENT_SOURCE_DIR}/dist) 

include(GetSystemVersion)
include(BuildOptions)

message(STATUS "Subsystem: ${SUBSYSTEM_NAME}")

message(STATUS "**** Third-party ****")
list(APPEND CMAKE_MODULE_PATH ${THIRD_PARTY_DIR}/indigo/common/cmake/)
include(ConfigureCommon)
set(WITH_STATIC ON)
add_subdirectory(${THIRD_PARTY_DIR}/indigo/build_scripts/indigo)
add_subdirectory(${THIRD_PARTY_DIR}/indigo/build_scripts/indigo-inchi)

message(STATUS "**** Imago ****")
add_subdirectory(imago)

if(SUBSYSTEM_NAME STREQUAL "iOS")
	add_subdirectory(ireco)
else()
	add_subdirectory(font_generator)

	if(SYSTEM_NAME STREQUAL "Windows")
		# windows only tools
		add_subdirectory(tools/calculate_probability_matrices)
	endif()

	add_subdirectory(imago_c)

	if(Java_JAVAC_EXECUTABLE)
		Include(UseJava)
		add_subdirectory(imago_java)
		# add_subdirectory(ego)
	else()
		message(STATUS "Java is not found!")
	endif()

	add_subdirectory(imago_python)

	add_subdirectory(imago_console)
endif()
cmake_minimum_required(VERSION 2.8.6)

project("Imago")

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_CURRENT_SOURCE_DIR}/cmake/)

if(CMAKE_SYSTEM_NAME STREQUAL "Windows")
	if(NOT MSVC)
		message(FATAL_ERROR "Please build Imago with MSVC!")
	endif()
endif()

include(GetSystemVersion)
include(BuildOptions)

add_subdirectory(imago)

if(IRECO)
	add_subdirectory(ireco)
else()
	add_subdirectory(font_generator)

if(SYSTEM_NAME STREQUAL "Windows")
	# windows only tools
	add_subdirectory(tools/calculate_probability_matrices)
endif()
	add_subdirectory(imago_c)
	add_subdirectory(alter-ego)

	if(Java_JAVAC_EXECUTABLE)
		Include(UseJava)
		add_subdirectory(imago_java)
		add_subdirectory(ego)
	else()
		message("Java is not found!")
	endif()

	add_subdirectory(imago_console)
endif()

cmake_minimum_required(VERSION 2.8)

project("Imago")

#TODO: Add FindPackage with appropriate versions for OpenCV and Boost
set(INDIGO_INCLUDE_DIR  "${CMAKE_SOURCE_DIR}/third_party/indigo")
set(INDIGO_LIBS_DIR     "${CMAKE_SOURCE_DIR}/third_party/indigo")

set(OpenCV_DIR "${CMAKE_SOURCE_DIR}/third_party/opencv")
set(BOOST_INCLUDEDIR "${CMAKE_SOURCE_DIR}/third_party/boost")
set(BOOST_LIBRARYDIR "${CMAKE_SOURCE_DIR}/third_party/boost")

#if(NOT EXISTS "${INDIGO_INCLUDE_DIR}/")
#	message("Extracting Indigo")
#	execute_process(COMMAND ${CMAKE_COMMAND} -E tar xvf "${INDIGO_INCLUDE_DIR}.zip" WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}/third_party" OUTPUT_QUIET)
#endif()


if(CMAKE_SYSTEM_NAME STREQUAL "Windows")
	if(NOT MSVC)
		message(FATAL_ERROR "Please build Imago with MSVC!")
	endif()

	add_definitions("/D _CRT_SECURE_NO_DEPRECATE /D BOOST_ALL_NO_LIB")
	if(CMAKE_CL_64)
		set(INDIGO_LIBS_DIR "${INDIGO_LIBS_DIR}/win64")
		set(OpenCV_DIR "${OpenCV_DIR}/win64")
		set(BOOST_LIBRARYDIR "${BOOST_LIBRARYDIR}/win64")
	else()
		set(INDIGO_LIBS_DIR "${INDIGO_LIBS_DIR}/win32")
		set(OpenCV_DIR "${OpenCV_DIR}/win32")
		set(BOOST_LIBRARYDIR "${BOOST_LIBRARYDIR}/win32")
	endif()
elseif(CMAKE_SYSTEM_NAME STREQUAL "Linux")
	option(IMAGO_BITNESS "Target bitness" 64)

	find_package(Threads REQUIRED)
	if(${IMAGO_BITNESS} EQUAL 32)
		if(${CMAKE_SIZEOF_VOID_P} EQUAL 8)
			set(IMAGO_C_FLAGS "-m32")
		endif()

		set(INDIGO_LIBS_DIR "${INDIGO_LIBS_DIR}/linux32")
		set(OpenCV_DIR "${OpenCV_DIR}/linux32")
		set(BOOST_LIBRARYDIR "${BOOST_LIBRARYDIR}/linux32")
	elseif(${IMAGO_BITNESS} EQUAL 64)
		if(${CMAKE_SIZEOF_VOID_P} EQUAL 4)
			set(IMAGO_C_FLAGS "-m64")
		endif()

		set(INDIGO_LIBS_DIR "${INDIGO_LIBS_DIR}/linux64")
		set(OpenCV_DIR "${OpenCV_DIR}/linux64")
		set(BOOST_LIBRARYDIR "${BOOST_LIBRARYDIR}/linux64")
	else()
		message(FATAL_ERROR "Wrong bitness!")
	endif()

	message(FATAL_ERROR "Not tested yet")
elseif(CMAKE_SYSTEM_NAME STREQUAL "Darwin")
	option(IRECO "Build iOS application iReco" OFF)
	
	set(CMAKE_XCODE_ATTRIBUTE_GCC_VERSION "com.apple.compilers.llvmgcc42")

	if (IRECO)
		set(INDIGO_LIBS_DIR "${INDIGO_LIBS_DIR}/ios")
		set(OpenCV_DIR "${OpenCV_DIR}/ios/share/OpenCV")
		set(BOOST_LIBRARYDIR "${BOOST_LIBRARYDIR}/ios")
		
		SET (SDKVER "5.0")
		SET (DEVROOT "/Developer/Platforms/iPhoneOS.platform/Developer")
		SET (SDKROOT "${DEVROOT}/SDKs/iPhoneOS${SDKVER}.sdk")
		SET (CMAKE_OSX_SYSROOT "${SDKROOT}")
		SET (CMAKE_OSX_ARCHITECTURES "armv7;i386") #"$(ARCHS_STANDARD_32_BIT)") #"$(ARCHS_UNIVERSAL_IPHONE_OS)")
		SET (CMAKE_XCODE_EFFECTIVE_PLATFORMS "-iphoneos;-iphonesimulator")
		#Other 'CMAKE_OSX_ARCHITECTURES' iPhone/IOS option examples
		#SET (CMAKE_OSX_ARCHITECTURES "armv7")
		#SET (CMAKE_OSX_ARCHITECTURES $(ARCHS_STANDARD_32_BIT)		
	else()
		find_package(Threads REQUIRED)
		set(INDIGO_LIBS_DIR "${INDIGO_LIBS_DIR}/mac")	
		set(OpenCV_DIR "${OpenCV_DIR}/mac/share/OpenCV")
		set(BOOST_LIBRARYDIR "${BOOST_LIBRARYDIR}/mac")
		set(CMAKE_OSX_ARCHITECTURES "i386;x86_64")
		set(COMPILE_FLAGS "${COMPILE_FLAGS} -fPIC")
	endif()
endif()

file(GLOB INDIGO_LIBS "${INDIGO_LIBS_DIR}/*${CMAKE_STATIC_LIBRARY_SUFFIX}")

include("${OpenCV_DIR}/OpenCVConfig.cmake")

#set(Boost_DEBUG ON)
set(Boost_ADDITIONAL_VERSIONS "1.49" "1.49.0")
set(Boost_USE_STATIC_LIBS ON)
set(Boost_USE_MULTITHREADED ON)
set(Boost_USE_STATIC_RUNTIME OFF)
find_package(Boost 1.49.0 COMPONENTS thread program_options system filesystem)

#iOS supports only static libs!
if (NOT IRECO)
	option(IMAGO_SHARED "Build Imago shared library" OFF)
else()
	set(IMAGO_SHARED OFF)
endif()

include_directories(${Boost_INCLUDE_DIR})
include_directories(${INDIGO_INCLUDE_DIR})
include_directories(${OpenCV_INCLUDE_DIRS})

add_subdirectory(imago)

if(IRECO)
	#message(FATAL_ERROR "Not implemented yet")
	add_subdirectory(ireco)
else()
	#No need for this now
	add_subdirectory(font_generator)

if(CMAKE_SYSTEM_NAME STREQUAL "Windows")
	# windows only tools
	add_subdirectory(tools/constfuzzer)
	add_subdirectory(tools/timelimit)
	add_subdirectory(tools/calculate_probability_matrices)
endif()

	add_subdirectory(imago_c)
	add_subdirectory(alter-ego)
	add_subdirectory(tests/vs)
	add_subdirectory(tests/rc)
endif()

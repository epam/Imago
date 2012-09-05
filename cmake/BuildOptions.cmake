#TODO: Add FindPackage with appropriate versions for OpenCV and Boost
set(INDIGO_INCLUDE_DIR  "${CMAKE_SOURCE_DIR}/third_party/indigo")
set(INDIGO_LIBS_DIR     "${CMAKE_SOURCE_DIR}/third_party/indigo")

set(OpenCV_DIR "${CMAKE_SOURCE_DIR}/third_party/opencv")
set(BOOST_INCLUDEDIR "${CMAKE_SOURCE_DIR}/third_party/boost")
set(BOOST_LIBRARYDIR "${CMAKE_SOURCE_DIR}/third_party/boost")

if(SYSTEM_NAME STREQUAL "Win")
	include(BuildOptionsWin)
elseif(SYSTEM_NAME STREQUAL "Linux")
	include(BuildOptionsLinux)
elseif(SYSTEM_NAME STREQUAL "Mac")
	include(BuildOptionsMac)
endif()

if(UNIX OR APPLE)
    add_definitions("${IMAGO_C_FLAGS}")
    #add_definitions("-fvisibility=hidden")
    set(CMAKE_EXE_LINKER_FLAGS ${CMAKE_EXE_LINKER_FLAGS_INIT} ${IMAGO_C_FLAGS})
    set(CMAKE_SHARED_LINKER_FLAGS ${CMAKE_SHARED_LINKER_FLAGS_INIT} ${IMAGO_C_FLAGS})
    set(LINK_FLAGS "${LINK_FLAGS} ${IMAGO_C_FLAGS}")
endif()
 
#set(Boost_DEBUG ON)
set(Boost_ADDITIONAL_VERSIONS "1.49" "1.49.0")
set(Boost_USE_STATIC_LIBS ON)
set(Boost_USE_MULTITHREADED ON)
set(Boost_USE_STATIC_RUNTIME OFF)
find_package(Boost 1.49.0 COMPONENTS thread program_options system filesystem)
include_directories(${Boost_INCLUDE_DIR})

include("${OpenCV_DIR}/OpenCVConfig.cmake")
include_directories(${OpenCV_INCLUDE_DIRS})

include_directories(${INDIGO_INCLUDE_DIR})

if(NOT UNIX)
file(GLOB INDIGO_LIBS "${INDIGO_LIBS_DIR}/*${CMAKE_STATIC_LIBRARY_SUFFIX}")
endif()

Find_Package(Java)

set(CMAKE_INSTALL_SYSTEM_RUNTIME_LIBS_SKIP TRUE)
include(InstallRequiredSystemLibraries)
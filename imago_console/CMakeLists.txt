include_directories(
  ../imago/src
  )

file(GLOB SRC src/*.cpp)


if(UNIX OR APPLE)
    SET(COMPILE_FLAGS "${COMPILE_FLAGS} -fPIC")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -fPIC")
endif()


FILE(GLOB HEADERS "src/*.h")
list(APPEND SRC ${HEADERS})

INCLUDE_DIRECTORIES(${THIRD_PARTY_DIR}/opencv/include)

INCLUDE_DIRECTORIES(${THIRD_PARTY_DIR}/indigo/api)
INCLUDE_DIRECTORIES(${THIRD_PARTY_DIR}/indigo/api/plugins/inchi)
INCLUDE_DIRECTORIES(${THIRD_PARTY_DIR}/indigo/api/plugins/renderer)
INCLUDE_DIRECTORIES(${THIRD_PARTY_DIR}/indigo/common)
INCLUDE_DIRECTORIES(${THIRD_PARTY_DIR}/indigo/third_party/zlib/include)

INCLUDE_DIRECTORIES(${THIRD_PARTY_DIR}/opencv/modules/core/include)
INCLUDE_DIRECTORIES(${THIRD_PARTY_DIR}/opencv/modules/flann/include)
INCLUDE_DIRECTORIES(${THIRD_PARTY_DIR}/opencv/modules/contrib/include)
INCLUDE_DIRECTORIES(${THIRD_PARTY_DIR}/opencv/modules/features2d/include)
INCLUDE_DIRECTORIES(${THIRD_PARTY_DIR}/opencv/modules/calib3d/include)
INCLUDE_DIRECTORIES(${THIRD_PARTY_DIR}/opencv/modules/imgproc/include)
INCLUDE_DIRECTORIES(${THIRD_PARTY_DIR}/opencv/modules/objdetect/include)
INCLUDE_DIRECTORIES(${THIRD_PARTY_DIR}/opencv/modules/video/include)
INCLUDE_DIRECTORIES(${THIRD_PARTY_DIR}/opencv/modules/photo/include)
INCLUDE_DIRECTORIES(${THIRD_PARTY_DIR}/opencv/modules/ml/include)
INCLUDE_DIRECTORIES(${THIRD_PARTY_DIR}/opencv/modules/legacy/include)
INCLUDE_DIRECTORIES(${THIRD_PARTY_DIR}/opencv/modules/highgui/include)

include(${THIRD_PARTY_DIR}/indigo/common/cmake/GetSystemVersion.cmake)

message(STATUS "**** Indigo ****")
add_subdirectory(${THIRD_PARTY_DIR}/indigo/build_scripts/indigo ${CMAKE_CURRENT_BINARY_DIR}/indigo)
message(STATUS "**** Indigo-renderer  ****")
add_subdirectory(${THIRD_PARTY_DIR}/indigo/build_scripts/indigo-renderer ${CMAKE_CURRENT_BINARY_DIR}/indigo-renderer)

message(STATUS "****** OpenCV *******")
add_subdirectory(${THIRD_PARTY_DIR}/opencv/ ${CMAKE_CURRENT_BINARY_DIR}/opencv)

add_executable(imago_console ${SRC})
if(UNIX AND NOT APPLE)
	find_package(Freetype REQUIRED)
	target_link_libraries(imago_console freetype fontconfig)
endif()
if(APPLE)
    INCLUDE(MacFrameworks)
    FIND_FRAMEWORK(ApplicationServices)
    target_link_libraries(imago_console ${FRAMEWORK_ApplicationServices})
endif()
target_link_libraries(imago_console indigo indigo-renderer z tinyxml cairo pixman)
target_link_libraries(imago_console imago)

install(TARGETS imago_console RUNTIME  DESTINATION imago_console)

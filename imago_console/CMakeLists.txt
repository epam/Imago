include_directories(
  ../imago/src
  )

file(GLOB SRC src/*.cpp)

FILE(GLOB HEADERS "src/*.h")
list(APPEND SRC ${HEADERS})

INCLUDE_DIRECTORIES(${THIRD_PARTY_DIR}/boost/include)
INCLUDE_DIRECTORIES(${THIRD_PARTY_DIR}/opencv/include)
INCLUDE_DIRECTORIES(${THIRD_PARTY_DIR}/indigo/api)
INCLUDE_DIRECTORIES(${THIRD_PARTY_DIR}/indigo/api/plugins/inchi)
INCLUDE_DIRECTORIES(${THIRD_PARTY_DIR}/indigo/api/plugins/renderer)
INCLUDE_DIRECTORIES(${THIRD_PARTY_DIR}/indigo/common)
INCLUDE_DIRECTORIES(${THIRD_PARTY_DIR}/indigo/third_party/zlib/include)
INCLUDE_DIRECTORIES(${THIRD_PARTY_DIR}/indigo/third_party/png/include)
INCLUDE_DIRECTORIES(${THIRD_PARTY_DIR}/opencv/include)
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


add_subdirectory(${THIRD_PARTY_DIR}/indigo/build_scripts/indigo-all ${CMAKE_CURRENT_BINARY_DIR}/indigo-all)
add_subdirectory(${THIRD_PARTY_DIR}/opencv/third_party/jpeg ${CMAKE_CURRENT_BINARY_DIR}/jpeg)
get_directory_property(JPEG_INCLUDE_DIR DIRECTORY ${THIRD_PARTY_DIR}/opencv/third_party/jpeg DEFINITION JPEG_INCLUDE_DIR)
add_subdirectory(${THIRD_PARTY_DIR}/opencv/third_party/tiff ${CMAKE_CURRENT_BINARY_DIR}/tiff)
get_directory_property(TIFF_INCLUDE_DIR DIRECTORY ${THIRD_PARTY_DIR}/opencv/third_party/tiff DEFINITION TIFF_INCLUDE_DIR)
add_subdirectory(${THIRD_PARTY_DIR}/opencv/ ${CMAKE_CURRENT_BINARY_DIR}/opencv)
add_subdirectory(${THIRD_PARTY_DIR}/boost/ ${CMAKE_CURRENT_BINARY_DIR}/boost)


add_executable(imago_console ${SRC})
if(UNIX AND NOT APPLE)
	find_package(Freetype REQUIRED)
	target_link_libraries(imago_console freetype fontconfig)
endif()
target_link_libraries(imago_console render2d indigo indigo-renderer common molecule reaction graph layout z tinyxml cairo pixman png)
target_link_libraries(imago_console imago)

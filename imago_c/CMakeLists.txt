include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../imago/src)
include_directories(${THIRD_PARTY_DIR}/boost/include)
include_directories(${THIRD_PARTY_DIR}/indigo/api)
include_directories(${THIRD_PARTY_DIR}/opencv/include)
include_directories(${THIRD_PARTY_DIR}/opencv/modules/core/include)
include_directories(${THIRD_PARTY_DIR}/opencv/modules/flann/include)
include_directories(${THIRD_PARTY_DIR}/opencv/modules/imgproc/include)
include_directories(${THIRD_PARTY_DIR}/opencv/modules/photo/include)
include_directories(${THIRD_PARTY_DIR}/opencv/modules/video/include)
include_directories(${THIRD_PARTY_DIR}/opencv/modules/features2d/include)
include_directories(${THIRD_PARTY_DIR}/opencv/modules/objdetect/include)
include_directories(${THIRD_PARTY_DIR}/opencv/modules/calib3d/include)
include_directories(${THIRD_PARTY_DIR}/opencv/modules/ml/include)
include_directories(${THIRD_PARTY_DIR}/opencv/modules/highgui/include)
include_directories(${THIRD_PARTY_DIR}/opencv/modules/contrib/include)

include(imago_version.cmake)
message(STATUS "Imago version is ${IMAGO_VERSION} (${IMAGO_VERSION_EXT})")
set(IMAGO_VERSION "${IMAGO_VERSION}" PARENT_SCOPE) # promote Imago version
configure_file(src/imago_version.h.in ${CMAKE_CURRENT_SOURCE_DIR}/src/imago_version.h)

if(UNIX OR APPLE)
    SET(COMPILE_FLAGS "${COMPILE_FLAGS} -std=c++11 -fPIC")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -fPIC")
endif()


file(GLOB SRC src/*.cpp)
file(GLOB HEADERS src/*.h)
list(APPEND SRC ${HEADERS})

#SHARED
add_library(imago_c_shared SHARED ${SRC})
add_dependencies(imago_c_shared imago)
target_link_libraries(imago_c_shared imago)
set_target_properties(imago_c_shared PROPERTIES
	OUTPUT_NAME imago_c
	LIBRARY_OUTPUT_DIRECTORY imago_shared)

install(TARGETS imago_c_shared EXPORT imago DESTINATION imago_shared)
install(FILES src/imago_c.h DESTINATION imago_shared RENAME imago.h)
install(FILES ${CMAKE_INSTALL_SYSTEM_RUNTIME_LIBS} DESTINATION imago_shared)

#STATIC
add_library(imago_c_static STATIC ${SRC})
add_dependencies(imago_c_static imago)
target_link_libraries(imago_c_static imago)
set_target_properties(imago_c_static PROPERTIES
	OUTPUT_NAME imago_c
	ARCHIVE_OUTPUT_DIRECTORY imago_static)

install(TARGETS imago_c_static EXPORT imago DESTINATION imago_static)
install(FILES src/imago_c.h DESTINATION imago_static RENAME imago.h)

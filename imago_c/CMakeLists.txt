include_directories(../imago/src)
include_directories(${Boost_INCLUDE_DIR})
include_directories(${INDIGO_INCLUDE_DIR})
include_directories(${OpenCV_INCLUDE_DIRS})

include(imago_version.cmake)
message(STATUS "Imago version is ${IMAGO_VERSION} (${IMAGO_VERSION_EXT})")
set(IMAGO_VERSION "${IMAGO_VERSION}" PARENT_SCOPE) # promote Imago version
configure_file(src/imago_version.h.in ${CMAKE_CURRENT_SOURCE_DIR}/src/imago_version.h)

file(GLOB SRC src/*.cpp)
file(GLOB HEADERS src/*.h)
list(APPEND SRC ${HEADERS})

add_library(imago_c_shared SHARED ${SRC})
add_dependencies(imago_c_shared imago)
target_link_libraries(imago_c_shared imago)
set_target_properties(imago_c_shared PROPERTIES OUTPUT_NAME "imago_c")
#get_target_property(NAME imago_c_shared OUTPUT_NAME)
#message(${NAME})

add_library(imago_c_static STATIC ${SRC})
add_dependencies(imago_c_static imago)
target_link_libraries(imago_c_static imago)
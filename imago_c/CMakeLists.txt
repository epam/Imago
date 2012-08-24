include_directories(../imago/src)
include_directories(${Boost_INCLUDE_DIR})
include_directories(${INDIGO_INCLUDE_DIR})
include_directories(${OpenCV_INCLUDE_DIRS})

set(SRC
  src/imago_c.cpp
  )

file(GLOB SRC src/*.cpp)
file(GLOB HEADERS src/*.h)
list(APPEND SRC ${HEADERS})

add_library(imago_c_shared SHARED ${SRC})
add_dependencies(imago_c_shared imago)
target_link_libraries(imago_c_shared imago)

add_library(imago_c STATIC ${SRC})
add_dependencies(imago_c imago)
target_link_libraries(imago_c imago)
include_directories(../imago/src)
include_directories(${Boost_INCLUDE_DIR})
include_directories(${INDIGO_INCLUDE_DIR})
include_directories(${OpenCV_INCLUDE_DIRS})

set(SRC
  src/imago_c.cpp
  )

file(GLOB SRC src/*.cpp)
file(GLOB SRC_posix src/*_posix.cpp)
file(GLOB SRC_win src/*_win.cpp)

FILE(GLOB HEADERS "src/*.h")
list(APPEND SRC ${HEADERS})

#if(WIN32)
#  list(REMOVE_ITEM SRC ${SRC_posix})
#else(WIN32)
#  list(REMOVE_ITEM SRC ${SRC_win})
#endif(WIN32)

#if(${IMAGO_SHARED})
	add_library(imago_c_shared SHARED ${SRC})
	add_dependencies(imago_c_shared imago)
	target_link_libraries(imago_c_shared imago)
#else()
	add_library(imago_c STATIC ${SRC})
#endif()

add_dependencies(imago_c imago)
target_link_libraries(imago_c imago)
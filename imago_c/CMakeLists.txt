include_directories(../imago/src)
include_directories(${Boost_INCLUDE_DIR})
include_directories(${INDIGO_INCLUDE_DIR})
include_directories(${OpenCV_INCLUDE_DIRS})

set(SRC
  src/imago_c.cpp
  )

FILE(GLOB HEADERS "src/*.h")
list(APPEND SRC ${HEADERS})

if(${IMAGO_SHARED})
	add_library(imago_c SHARED ${SRC})
else()
	add_library(imago_c STATIC ${SRC})
endif()

add_dependencies(imago_c imago)
target_link_libraries(imago_c imago)
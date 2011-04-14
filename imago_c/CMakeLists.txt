include_directories(
  ..
  ../imago/src
  ../libpng/src
  )

set(SRC
  src/imago_c.cpp
  )

FILE(GLOB HEADERS "src/*.h")
list(APPEND SRC ${HEADERS})

add_library(imago_c SHARED ${SRC})
target_link_libraries(imago_c imago_static)

add_library(imago_c_static STATIC ${SRC})
target_link_libraries(imago_c_static imago_static)

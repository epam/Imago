include_directories(
  ..
  ../imago/src
  )

set(SRC
  src/imago_c.cpp
  )

add_library(imago_c SHARED ${SRC})
target_link_libraries(imago_c imago_static)

add_library(imago_c_static STATIC ${SRC})
target_link_libraries(imago_c_static imago_static)
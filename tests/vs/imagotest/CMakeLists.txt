include_directories(
  ../../../
  ../../../imago/src
  ../../../libpng/src
  )

set(SRC
  src/main.cpp
  )

add_executable(imagotest ${SRC})
target_link_libraries(imagotest imago_static)
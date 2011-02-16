include_directories(
  ../../
  ../../imago/src
  ../../libpng/src
  )

set(SRC
  main.cpp
  )

add_executable(dptest ${SRC})
target_link_libraries(dptest imago_static)
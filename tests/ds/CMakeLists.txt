include_directories(
  ../../
  ../../imago/src
  ../../opencv/include
  ../../version
  )

set(SRC
  main.cpp
  )

add_executable(ds_test ${SRC})
target_link_libraries(ds_test imago_static)
include_directories(
  ../../
  ../../imago/src
  ../../opencv/include
  )

set(SRC
  main.cpp
  )

add_executable(fztest ${SRC})
target_link_libraries(fztest imago_static)
include_directories(
  ../../
  ../../imago/src
  )

set(SRC
  main.cpp
  )

add_executable(fztest ${SRC})
target_link_libraries(fztest imago_static)
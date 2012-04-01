include_directories(
  ../../imago/src
  )

set(SRC
  src/main.cpp
  )

add_executable(test.vs ${SRC})
target_link_libraries(test.vs imago)
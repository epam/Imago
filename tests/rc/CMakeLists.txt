include_directories(
  ../../imago/src
  )

set(SRC
  src/main.cpp
  )

add_executable(test.rc ${SRC})
target_link_libraries(test.rc imago)
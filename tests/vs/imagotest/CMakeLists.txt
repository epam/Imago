include_directories(
  ../../../
  ../../../imago/src
  ${OpenCV_INCLUDE_DIRS}
  )

set(SRC
  src/main.cpp
  )

add_executable(imagotest ${SRC})
target_link_libraries(imagotest imago_static)
include_directories(../imago/src)

set(SRC
  src/font_generator.cpp
  )

add_executable(font_generator ${SRC})

add_dependencies(font_generator imago)
target_link_libraries(font_generator imago)
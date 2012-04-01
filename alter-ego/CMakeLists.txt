include_directories(../imago_c/src)

set(SRC
  src/alter_ego.cpp
  )

add_executable(alter_ego ${SRC})

add_dependencies(alter_ego imago_c)
target_link_libraries(alter_ego imago_c)
include_directories(
  ../../imago_c/src
  )

set(SRC
  imagojni.cpp
  )

add_library(imagojni SHARED ${SRC})
target_link_libraries(imagojni imago_c_static)
target_link_libraries(imagojni jpeg png)

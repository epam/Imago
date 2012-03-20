include_directories(
  ..
  ../imago/src
  )

set(SRC
  src/font_data.cpp
  )

FILE(GLOB HEADERS "src/*.h")
list(APPEND SRC ${HEADERS})

add_library(font_lib STATIC ${SRC})


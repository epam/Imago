
set(SRC
  timelimit.cpp
  )

add_definitions(-DUNICODE -D_UNICODE)
add_executable(timelimit ${SRC})

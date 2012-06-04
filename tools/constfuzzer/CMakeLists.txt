
set(SRC
  constfuzzer.cpp
  )

add_definitions(-DUNICODE -D_UNICODE)
add_executable(constfuzzer ${SRC})

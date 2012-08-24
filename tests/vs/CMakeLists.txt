include_directories(
  ../../imago/src
  )

set(SRC
  src/main.cpp
  )

add_library(test.vs SHARED ${SRC})
target_link_libraries(test.vs imago)

if(UNIX OR APPLE)
    SET(COMPILE_FLAGS "${COMPILE_FLAGS} -fPIC")
endif()

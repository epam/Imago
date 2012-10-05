include_directories(
  ../../imago/src
  )

file(GLOB SRC src/*.cpp)

FILE(GLOB HEADERS "src/*.h")
list(APPEND SRC ${HEADERS})

add_executable(test.rc ${SRC})
target_link_libraries(test.rc imago)
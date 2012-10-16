include_directories(
  ../imago/src
  )

file(GLOB SRC src/*.cpp)

FILE(GLOB HEADERS "src/*.h")
list(APPEND SRC ${HEADERS})

add_executable(imago_console ${SRC})
target_link_libraries(imago_console imago)
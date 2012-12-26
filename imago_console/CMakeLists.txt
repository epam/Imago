include_directories(
  ../imago/src
  )

file(GLOB SRC src/*.cpp)

FILE(GLOB HEADERS "src/*.h")
list(APPEND SRC ${HEADERS})

add_executable(imago_console ${SRC})
if(UNIX AND NOT APPLE)
	find_package(Freetype REQUIRED)
	target_link_libraries(imago_console freetype fontconfig)
endif()
target_link_libraries(imago_console ${INDIGO_LIBS})
target_link_libraries(imago_console imago)

project(imago)
cmake_minimum_required(VERSION 2.6)

if(NOT WIN32)
  option(CROSS32 "Cross-compile for 32-bit" OFF)
  find_package(Threads REQUIRED)
endif(NOT WIN32)

if(CROSS32)
  SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -m32")
  SET(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -m32")
endif(CROSS32)

option(EMBED_FONT "Embed font file" ON)

#message("CMAKE_CXX_FLAGS = ${CMAKE_CXX_FLAGS}")
#message("CMAKE_C_FLAGS = ${CMAKE_C_FLAGS}")

add_subdirectory(libpng)
add_subdirectory(libjpeg)
add_subdirectory(leptonlib)

add_subdirectory(imago)
add_subdirectory(imago_c)
add_subdirectory(alter-ego)
add_subdirectory(jimago)

add_subdirectory(tests/vs/imagotest)
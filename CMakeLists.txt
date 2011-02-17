project(imago)
cmake_minimum_required(VERSION 2.6)

if(NOT WIN32)
  option(CROSS32 "Cross-compile for 32-bit" OFF)
  find_package(Threads REQUIRED)
  
  find_package(PNG REQUIRED)
  find_package(JPEG REQUIRED)
  
  set(IMAGO_C_FLAGS "-fPIC")
else(NOT WIN32)

  add_subdirectory(libpng)
  add_subdirectory(libjpeg)
  
  set(PNG_INCLUDE_DIR ${CMAKE_SOURCE_DIR}/libpng/src)
  set(PNG_LIBRARIES png_local)
  
  set(JPEG_INCLUDE_DIR ${CMAKE_SOURCE_DIR}/libjpeg)
  set(JPEG_LIBRARIES jpeg_local)
endif(NOT WIN32)

if(CROSS32)
  set(IMAGO_C_FLAGS "${IMAGO_C_FLAGS} -m32")
endif(CROSS32)

option(EMBED_FONT "Embed font file" ON)

#add_definitions(${IMAGO_C_FLAGS})
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${IMAGO_C_FLAGS}")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${IMAGO_C_FLAGS}")

#message("CMAKE_CXX_FLAGS = ${CMAKE_CXX_FLAGS}")
#message("CMAKE_C_FLAGS = ${CMAKE_C_FLAGS}")


add_subdirectory(leptonlib)

add_subdirectory(imago)
add_subdirectory(imago_c)
add_subdirectory(alter-ego)
add_subdirectory(jimago)

add_subdirectory(tests/vs/imagotest)
add_subdirectory(tests/dp)

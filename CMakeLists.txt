project(imago)
cmake_minimum_required(VERSION 2.6)

macro(LOCAL_PNG)
  add_subdirectory(libpng)
  set(PNG_INCLUDE_DIR ${CMAKE_SOURCE_DIR}/libpng/src)
  set(PNG_LIBRARIES png_local)
endmacro(LOCAL_PNG)

macro(LOCAL_JPEG)
  add_subdirectory(libjpeg)
  set(JPEG_INCLUDE_DIR ${CMAKE_SOURCE_DIR}/libjpeg)
  set(JPEG_LIBRARIES jpeg_local)
endmacro(LOCAL_JPEG)

set(INDIGO_INCLUDE_DIR ${CMAKE_SOURCE_DIR}/third_party/indigo)

if(NOT WIN32)
  option(CROSS32 "Cross-compile for 32-bit" OFF)

  set(IMAGO_C_FLAGS "-fPIC")
  if(CROSS32)
    set(INDIGO_LIBS_DIR ${CMAKE_SOURCE_DIR}/third_party/indigo/linux32/)
    set(IMAGO_C_FLAGS "${IMAGO_C_FLAGS} -m32")
  else(CROSS32)
    set(INDIGO_LIBS_DIR ${CMAKE_SOURCE_DIR}/third_party/indigo/linux64/)
  endif(CROSS32)

 
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${IMAGO_C_FLAGS}")
  set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${IMAGO_C_FLAGS}")

  message(${CMAKE_CXX_FLAGS})

  find_package(Threads REQUIRED)
  
  if(NOT APPLE)
    find_package(PNG REQUIRED)
    #find_package(JPEG REQUIRED)
    LOCAL_JPEG()

    find_package(OpenCV REQUIRED)
#    set(OpenCV_LIBS debug cxcore optimized cxcore
#        debug cv optimized cv)
  else(NOT APPLE)
    option(IPHONE "Cross-compile for IPHONE" OFF)

	  if (IPHONE)
            set(INDIGO_LIBS_DIR ${CMAKE_SOURCE_DIR}/third_party/indigo/ios)
	    set(IMAGO_C_FLAGS "${IMAGO_C_FLAGS} -mno-thumb -ffast-math -fvisibility=hidden")
	  endif (IPHONE)
  
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${IMAGO_C_FLAGS}")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${IMAGO_C_FLAGS}")

    LOCAL_PNG()
    LOCAL_JPEG()

    set(OpenCV_INCLUDE_DIRS ${CMAKE_SOURCE_DIR}/opencv/include)

    if(NOT IPHONE)
      set(OpenCV_LIBS 
          /Users/vsmolov/opencv/opencv/Output3/tmp/mac-install/lib/libopencv_core.a
          /Users/vsmolov/opencv/opencv/Output3/tmp/mac-install/lib/libopencv_imgproc.a
          /Users/vsmolov/opencv/opencv/Output3/tmp/mac-build/3rdparty/lib/Release/liblibjpeg.a
          /Users/vsmolov/opencv/opencv/Output3/tmp/mac-build/3rdparty/lib/Release/libopencv_lapack.a
         )
    endif(NOT IPHONE)
 
    
  endif(NOT APPLE)
 set(INDIGO_LIBS 
      ${INDIGO_LIBS_DIR}/libindigo.a
      ${INDIGO_LIBS_DIR}/libreaction.a
      ${INDIGO_LIBS_DIR}/liblayout.a
      ${INDIGO_LIBS_DIR}/libmolecule.a
      ${INDIGO_LIBS_DIR}/libgraph.a  
      ${INDIGO_LIBS_DIR}/libtinyxml.a      
     )

else(NOT WIN32)
  set(IMAGO_C_FLAGS "/MP /GL- /GR- /EHsc /Gy /W3 /nologo /c /wd4345 /wd4244 /D _CRT_SECURE_NO_DEPRECATE")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${IMAGO_C_FLAGS}")
  set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${IMAGO_C_FLAGS}")

  LOCAL_PNG()
  LOCAL_JPEG()  

  set(OpenCV_INCLUDE_DIRS ${CMAKE_SOURCE_DIR}/opencv/include)

  if(${CMAKE_SIZEOF_VOID_P} EQUAL 4) 
    set(OpenCV_LIBS_DIR ${CMAKE_SOURCE_DIR}/opencv/x86/lib)
    set(INDIGO_LIBS_DIR ${CMAKE_SOURCE_DIR}/third_party/indigo/win32/)
  else(${CMAKE_SIZEOF_VOID_P} EQUAL 4)
    set(OpenCV_LIBS_DIR ${CMAKE_SOURCE_DIR}/opencv/x64/lib)    
    set(INDIGO_LIBS_DIR ${CMAKE_SOURCE_DIR}/third_party/indigo/win64/)
  endif(${CMAKE_SIZEOF_VOID_P} EQUAL 4)

  set(INDIGO_LIBS 
      ${INDIGO_LIBS_DIR}/indigo.lib
      ${INDIGO_LIBS_DIR}/reaction.lib
      ${INDIGO_LIBS_DIR}/layout.lib
      ${INDIGO_LIBS_DIR}/molecule.lib
      ${INDIGO_LIBS_DIR}/graph.lib  
      ${INDIGO_LIBS_DIR}/tinyxml.lib      
     )

  set(OpenCV_LIBS optimized ${OpenCV_LIBS_DIR}/opencv_core220.lib
                  debug    ${OpenCV_LIBS_DIR}/opencv_core220d.lib
                  optimized ${OpenCV_LIBS_DIR}/opencv_imgproc220.lib
                  debug    ${OpenCV_LIBS_DIR}/opencv_imgproc220d.lib)
#                  optimized ${OpenCV_LIBS_DIR}/opencv_highgui220.lib
#                  debug    ${OpenCV_LIBS_DIR}/opencv_highgui220d.lib)
endif(NOT WIN32)

option(EMBED_FONT "Embed font file" ON)

#add_definitions(${IMAGO_C_FLAGS})
#message("CMAKE_CXX_FLAGS = ${CMAKE_CXX_FLAGS}")
#message("CMAKE_C_FLAGS = ${CMAKE_C_FLAGS}")
message(${CMAKE_SIZEOF_VOID_P})

add_subdirectory(imago)
if(NOT IPHONE)
add_subdirectory(imago_c)
add_subdirectory(alter-ego)
add_subdirectory(jimago)
add_subdirectory(mol-compare)

add_subdirectory(tests/vs/imagotest)
# add_subdirectory(tests/dp)
#add_subdirectory(tests/fz)
#add_subdirectory(tests/ds)
endif(NOT IPHONE)

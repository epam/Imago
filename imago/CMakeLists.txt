#Embedding font file
if(NOT EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/src/imago.font")
	message(WARNING "Font file missing")
endif()
if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/src/imago.font.inc")
	file(REMOVE "src/imago.font.inc")
endif()
file(STRINGS "src/imago.font" FONT_STRINGS)
foreach(line IN LISTS FONT_STRINGS)
	file(APPEND "src/imago.font.inc" "\"${line}\\n\",\n")
endforeach()
file(APPEND "src/imago.font.inc" "0\n")
#

file(GLOB SRC src/*.cpp)
file(GLOB SRC_posix src/*_posix.cpp)
file(GLOB SRC_win src/*_win.cpp)

FILE(GLOB HEADERS "src/*.h")
list(APPEND SRC ${HEADERS})

if(WIN32)
  list(REMOVE_ITEM SRC ${SRC_posix})
else(WIN32)
  list(REMOVE_ITEM SRC ${SRC_win})
endif(WIN32)

if (${IMAGO_SHARED})
  add_library(imago SHARED ${SRC})
else (${IMAGO_SHARED})
  add_library(imago STATIC ${SRC})
endif (${IMAGO_SHARED})

add_dependencies(imago OpenCV)
target_link_libraries(imago ${CMAKE_THREAD_LIBS_INIT})
target_link_libraries(imago ${INDIGO_LIBS})
target_link_libraries(imago ${OpenCV_LIBS})
target_link_libraries(imago ${Boost_LIBRARIES}) 

if(IRECO)
set_target_properties(imago PROPERTIES
#    XCODE_ATTRIBUTE_GCC_FAST_MATH YES
    XCODE_ATTRIBUTE_GCC_INLINES_ARE_PRIVATE_EXTERN YES
    XCODE_ATTRIBUTE_GCC_SYMBOLS_PRIVATE_EXTERN YES
#    XCODE_ATTRIBUTE_GCC_THUMB_SUPPORT NO
)
endif()

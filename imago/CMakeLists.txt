file(GLOB SRC src/*.cpp)

FILE(GLOB HEADERS "src/*.h") 
list(APPEND SRC ${HEADERS})


INCLUDE_DIRECTORIES(${THIRD_PARTY_DIR}/boost/include)
INCLUDE_DIRECTORIES(${THIRD_PARTY_DIR}/opencv/include)
INCLUDE_DIRECTORIES(${THIRD_PARTY_DIR}/indigo/api)
INCLUDE_DIRECTORIES(${THIRD_PARTY_DIR}/indigo/api/plugins/indigo-inchi)
INCLUDE_DIRECTORIES(${THIRD_PARTY_DIR}/indigo/api/plugins/indigo-renderer)
INCLUDE_DIRECTORIES(${THIRD_PARTY_DIR}/indigo/common)
INCLUDE_DIRECTORIES(${THIRD_PARTY_DIR}/opencv/include)
INCLUDE_DIRECTORIES(${THIRD_PARTY_DIR}/opencv/modules/core/include)
INCLUDE_DIRECTORIES(${THIRD_PARTY_DIR}/opencv/modules/flann/include)
INCLUDE_DIRECTORIES(${THIRD_PARTY_DIR}/opencv/modules/contrib/include)
INCLUDE_DIRECTORIES(${THIRD_PARTY_DIR}/opencv/modules/features2d/include)
INCLUDE_DIRECTORIES(${THIRD_PARTY_DIR}/opencv/modules/calib3d/include)
INCLUDE_DIRECTORIES(${THIRD_PARTY_DIR}/opencv/modules/imgproc/include)
INCLUDE_DIRECTORIES(${THIRD_PARTY_DIR}/opencv/modules/objdetect/include)
INCLUDE_DIRECTORIES(${THIRD_PARTY_DIR}/opencv/modules/video/include)
INCLUDE_DIRECTORIES(${THIRD_PARTY_DIR}/opencv/modules/photo/include)
INCLUDE_DIRECTORIES(${THIRD_PARTY_DIR}/opencv/modules/ml/include)
INCLUDE_DIRECTORIES(${THIRD_PARTY_DIR}/opencv/modules/legacy/include)
INCLUDE_DIRECTORIES(${THIRD_PARTY_DIR}/opencv/modules/highgui/include)

add_library(imago STATIC ${SRC})

target_link_libraries(imago ${CMAKE_THREAD_LIBS_INIT})
target_link_libraries(imago render2d indigo indigo-renderer common molecule reaction graph layout z tinyxml cairo pixman png)
target_link_libraries(imago opencv_contrib opencv_features2d opencv_video opencv_calib3d opencv_objdetect opencv_imgproc opencv_core opencv_ml opencv_photo opencv_legacy opencv_highgui opencv_gpu opencv_flann)
target_link_libraries(imago boost_chrono boost_thread boost_system boost_program_options boost_filesystem boost_date_time)
#target_link_libraries(imago ${INDIGO_LIBS})
#target_link_libraries(imago ${OpenCV_LIBS})
#target_link_libraries(imago ${Boost_LIBRARIES}) 

if(IRECO)
set_target_properties(imago PROPERTIES
#    XCODE_ATTRIBUTE_GCC_FAST_MATH YES
    XCODE_ATTRIBUTE_GCC_INLINES_ARE_PRIVATE_EXTERN YES
    XCODE_ATTRIBUTE_GCC_SYMBOLS_PRIVATE_EXTERN YES
#    XCODE_ATTRIBUTE_GCC_THUMB_SUPPORT NO
)
endif()

file(GLOB SRC src/*.cpp)

FILE(GLOB HEADERS "src/*.h")
list(APPEND SRC ${HEADERS})


include_directories(${THIRD_PARTY_DIR}/boost/include)
include_directories(${THIRD_PARTY_DIR}/indigo/api)
include_directories(${THIRD_PARTY_DIR}/indigo/api/plugins/indigo-inchi)
include_directories(${THIRD_PARTY_DIR}/indigo/api/plugins/indigo-renderer)
include_directories(${THIRD_PARTY_DIR}/indigo/common)
include_directories(${THIRD_PARTY_DIR}/opencv/include)
include_directories(${THIRD_PARTY_DIR}/opencv/modules/core/include)
include_directories(${THIRD_PARTY_DIR}/opencv/modules/flann/include)
include_directories(${THIRD_PARTY_DIR}/opencv/modules/contrib/include)
include_directories(${THIRD_PARTY_DIR}/opencv/modules/features2d/include)
include_directories(${THIRD_PARTY_DIR}/opencv/modules/calib3d/include)
include_directories(${THIRD_PARTY_DIR}/opencv/modules/imgproc/include)
include_directories(${THIRD_PARTY_DIR}/opencv/modules/objdetect/include)
include_directories(${THIRD_PARTY_DIR}/opencv/modules/video/include)
include_directories(${THIRD_PARTY_DIR}/opencv/modules/photo/include)
include_directories(${THIRD_PARTY_DIR}/opencv/modules/ml/include)
include_directories(${THIRD_PARTY_DIR}/opencv/modules/legacy/include)
include_directories(${THIRD_PARTY_DIR}/opencv/modules/highgui/include)

add_library(imago STATIC ${SRC})

target_link_libraries(imago ${CMAKE_THREAD_LIBS_INIT})
target_link_libraries(imago render2d indigo indigo-renderer common molecule reaction graph layout z tinyxml cairo pixman png)
target_link_libraries(imago opencv_contrib opencv_features2d opencv_video opencv_calib3d opencv_objdetect opencv_imgproc opencv_core opencv_ml opencv_photo opencv_legacy opencv_highgui opencv_gpu opencv_flann)
target_link_libraries(imago boost_chrono boost_thread boost_system boost_program_options boost_filesystem boost_date_time)

if(IRECO)
set_target_properties(imago PROPERTIES
#    XCODE_ATTRIBUTE_GCC_FAST_MATH YES
    XCODE_ATTRIBUTE_GCC_INLINES_ARE_PRIVATE_EXTERN YES
    XCODE_ATTRIBUTE_GCC_SYMBOLS_PRIVATE_EXTERN YES
#    XCODE_ATTRIBUTE_GCC_THUMB_SUPPORT NO
)
endif()

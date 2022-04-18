file(GLOB SRC src/*.cpp)

add_library(imago-core STATIC ${SRC})
target_include_directories(imago-core SYSTEM
        PUBLIC ${CMAKE_BINARY_DIR}
        PUBLIC ${IMAGO_THIRD_PARTY_DIR}/opencv/include
        PUBLIC ${IMAGO_THIRD_PARTY_DIR}/opencv/modules/calib3d/include
        PUBLIC ${IMAGO_THIRD_PARTY_DIR}/opencv/modules/core/include
        PUBLIC ${IMAGO_THIRD_PARTY_DIR}/opencv/modules/dnn/include
        PUBLIC ${IMAGO_THIRD_PARTY_DIR}/opencv/modules/features2d/include
        PUBLIC ${IMAGO_THIRD_PARTY_DIR}/opencv/modules/flann/include
        PUBLIC ${IMAGO_THIRD_PARTY_DIR}/opencv/modules/highgui/include
        PUBLIC ${IMAGO_THIRD_PARTY_DIR}/opencv/modules/imgcodecs/include
        PUBLIC ${IMAGO_THIRD_PARTY_DIR}/opencv/modules/imgproc/include
        PUBLIC ${IMAGO_THIRD_PARTY_DIR}/opencv/modules/ml/include
        PUBLIC ${IMAGO_THIRD_PARTY_DIR}/opencv/modules/objdetect/include
        PUBLIC ${IMAGO_THIRD_PARTY_DIR}/opencv/modules/photo/include
        PUBLIC ${IMAGO_THIRD_PARTY_DIR}/opencv/modules/stitching/include
        PUBLIC ${IMAGO_THIRD_PARTY_DIR}/opencv/modules/video/include
        PUBLIC ${IMAGO_THIRD_PARTY_DIR}/opencv/modules/videoio/include
        PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src
)

target_link_libraries(imago-core indigo-static opencv_core opencv_imgcodecs opencv_imgproc)

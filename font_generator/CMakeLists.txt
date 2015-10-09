include_directories(../imago/src)
include_directories(${THIRD_PARTY_DIR}/boost/include)
include_directories(${THIRD_PARTY_DIR}/opencv/include)
include_directories(${THIRD_PARTY_DIR}/opencv/modules/core/include)
include_directories(${THIRD_PARTY_DIR}/opencv/modules/flann/include)
include_directories(${THIRD_PARTY_DIR}/opencv/modules/imgproc/include)
include_directories(${THIRD_PARTY_DIR}/opencv/modules/photo/include)
include_directories(${THIRD_PARTY_DIR}/opencv/modules/video/include)
include_directories(${THIRD_PARTY_DIR}/opencv/modules/features2d/include)
include_directories(${THIRD_PARTY_DIR}/opencv/modules/objdetect/include)
include_directories(${THIRD_PARTY_DIR}/opencv/modules/calib3d/include)
include_directories(${THIRD_PARTY_DIR}/opencv/modules/ml/include)
include_directories(${THIRD_PARTY_DIR}/opencv/modules/highgui/include)
include_directories(${THIRD_PARTY_DIR}/opencv/modules/contrib/include)

set(SRC
  src/font_generator.cpp
  )

add_executable(font_generator ${SRC})

add_dependencies(font_generator imago)
target_link_libraries(font_generator imago)
file(GLOB SRC src/*.cpp)

FILE(GLOB HEADERS "src/*.h")
list(APPEND SRC ${HEADERS})

if(UNIX OR APPLE)
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fPIC")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -fPIC")
endif()

include_directories(${CMAKE_BINARY_DIR})
include_directories(${THIRD_PARTY_DIR}/opencv/include)
include_directories(${THIRD_PARTY_DIR}/opencv/modules/core/include)
include_directories(${THIRD_PARTY_DIR}/opencv/modules/flann/include)
include_directories(${THIRD_PARTY_DIR}/opencv/modules/features2d/include)
include_directories(${THIRD_PARTY_DIR}/opencv/modules/calib3d/include)
include_directories(${THIRD_PARTY_DIR}/opencv/modules/imgproc/include)
include_directories(${THIRD_PARTY_DIR}/opencv/modules/objdetect/include)
include_directories(${THIRD_PARTY_DIR}/opencv/modules/video/include)
include_directories(${THIRD_PARTY_DIR}/opencv/modules/photo/include)
include_directories(${THIRD_PARTY_DIR}/opencv/modules/ml/include)
include_directories(${THIRD_PARTY_DIR}/opencv/modules/highgui/include)
include_directories(${THIRD_PARTY_DIR}/opencv/modules/dnn/include)
include_directories(${THIRD_PARTY_DIR}/opencv/modules/imgcodecs/include)
include_directories(${THIRD_PARTY_DIR}/opencv/modules/videoio/include)
include_directories(${THIRD_PARTY_DIR}/opencv/modules/stitching/include)

add_library(imago STATIC ${SRC})

target_link_libraries(imago ${CMAKE_THREAD_LIBS_INIT})
target_link_libraries(imago indigo z tinyxml2 cairo pixman png)
target_link_libraries(imago opencv_imgproc opencv_core opencv_imgcodecs)

if(IRECO)
    set_target_properties(imago PROPERTIES
            XCODE_ATTRIBUTE_GCC_INLINES_ARE_PRIVATE_EXTERN YES
            XCODE_ATTRIBUTE_GCC_SYMBOLS_PRIVATE_EXTERN YES
            )
endif()

include_directories(
  ../imago/src
)

file(GLOB SRC src/*.cpp)

if(UNIX OR APPLE)
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fPIC")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -fPIC")
endif()

FILE(GLOB HEADERS "src/*.h")

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

add_executable(imago_console ${SRC})
if(UNIX AND NOT APPLE)
    find_package(Freetype REQUIRED)
    target_link_libraries(imago_console freetype fontconfig)
endif()
if(APPLE)
    include(MacFrameworks)
    find_framework(ApplicationServices)
    target_link_libraries(imago_console ${FRAMEWORK_ApplicationServices})
endif()
target_link_libraries(imago_console imago indigo-renderer)

install(TARGETS imago_console RUNTIME DESTINATION imago_console)

enable_testing()
add_test(imago-console-test imago_console ${CMAKE_SOURCE_DIR}/tests/mk/images/2008007515_51_chem.png)

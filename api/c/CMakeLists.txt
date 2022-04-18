include(imago_version.cmake)
message(STATUS "Imago version is ${IMAGO_VERSION} (${IMAGO_VERSION_EXT})")
set(IMAGO_VERSION "${IMAGO_VERSION}" PARENT_SCOPE) # promote Imago version
configure_file(src/imago_version.h.in ${CMAKE_CURRENT_BINARY_DIR}/imago_version.h)

file(GLOB SRC src/*.cpp)

add_library(imago-c SHARED ${SRC})
target_include_directories(imago-c PUBLIC ${CMAKE_CURRENT_BINARY_DIR})
target_link_libraries(imago-c imago-core)
set_target_properties(imago-c PROPERTIES OUTPUT_NAME "imago")

# add_library(imago-c-static STATIC ${SRC})
# target_include_directories(imago-c PUBLIC ${CMAKE_CURRENT_BINARY_DIR})
# target_link_libraries(imago-c-static imago-core)
# set_target_properties(imago-c PROPERTIES OUTPUT_NAME "imago")

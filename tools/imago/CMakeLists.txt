file(GLOB SRC src/*.cpp)

add_executable(imago ${SRC})
if(UNIX AND NOT APPLE)
    find_package(Freetype REQUIRED)
    target_link_libraries(imago freetype fontconfig)
endif()
if(APPLE)
    find_library(APP_SERVICES_LIBRARY ApplicationServices)
    target_link_libraries(imago ${APP_SERVICES_LIBRARY})
endif()
target_link_libraries(imago imago-core indigo-renderer-static)

add_custom_command(TARGET imago POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E make_directory ${IMAGO_DIST_DIR}
        COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:imago> ${IMAGO_DIST_DIR})

if (IMAGO_ENABLE_TESTS)
    add_subdirectory(tests)
endif()

set(SRC src/font_generator.cpp)

add_executable(font-generator ${SRC})

target_link_libraries(font-generator imago-core)

if (IMAGO_ENABLE_TESTS)
    add_test(NAME font-generator-test COMMAND font-generator ${CMAKE_CURRENT_LIST_DIR}/symbols symbols.txt)
endif()

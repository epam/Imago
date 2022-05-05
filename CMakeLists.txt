cmake_minimum_required(VERSION 3.0)
project("Imago")

option(IMAGO_ENABLE_TESTS "Enable tests for Imago" ON)
if (IMAGO_ENABLE_TESTS)
    enable_testing()
endif()

set(IMAGO_DIST_DIR ${CMAKE_CURRENT_LIST_DIR}/dist)
set(IMAGO_THIRD_PARTY_DIR ${CMAKE_CURRENT_LIST_DIR}/third_party)

add_subdirectory(third_party)

include(third_party/indigo/cmake/setup.cmake)
string(APPEND CMAKE_C_FLAGS_RELEASE " -g")
string(APPEND CMAKE_CXX_FLAGS_RELEASE " -g")

add_subdirectory(core)
add_subdirectory(api)
add_subdirectory(tools)

find_package(Python3 COMPONENTS Interpreter REQUIRED)
if(NOT Python3_FOUND)
    message(WARNING "Python executable not found, imago-tests disabled")
else()
    add_test(NAME imago-tests
        COMMAND ${Python3_EXECUTABLE} run.py
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
    )
#    set_tests_properties(imago-tests PROPERTIES DEPENDS "imago;indigo-python")
endif()

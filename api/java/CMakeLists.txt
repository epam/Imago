find_package(Java)

if (NOT Java_FOUND)
    message(WARNING "Java not found, skip configuring Imago Java API")
else()
    include(UseJava)
    set(CMAKE_JAVA_INCLUDE_PATH lib/jna.jar)
    set(CMAKE_JAVA_TARGET_OUTPUT_NAME imago)

    file(GLOB_RECURSE imago-java_SRC RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} src/*.java)
    add_jar(imago-java ${imago-java_SRC})
    add_dependencies(imago-java imago-c)

    #Add manifest
    get_target_property(imago_jar_filename imago-java JAR_FILE)
    add_custom_command(TARGET imago-java POST_BUILD
            COMMAND "${Java_JAR_EXECUTABLE}" "ufm" "${imago_jar_filename}" "manifest.mf"
            WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

    #Add libraries
    set(IMAGO_DLL_DIR "com/epam/imago/${SYSTEM_NAME}/${SUBSYSTEM_NAME}")
    add_custom_command(TARGET imago-java POST_BUILD
            COMMAND "${CMAKE_COMMAND}" "-E" "make_directory" "${IMAGO_DLL_DIR}"
            WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR})

    foreach(lib ${CMAKE_INSTALL_SYSTEM_RUNTIME_LIBS})
        add_custom_command(TARGET imago-java POST_BUILD
                COMMAND "${CMAKE_COMMAND}" "-E" "copy" "${lib}" "${IMAGO_DLL_DIR}/"
                WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR})
    endforeach()

    add_custom_command(TARGET imago-java POST_BUILD
            COMMAND "${CMAKE_COMMAND}" "-E" "copy" "$<TARGET_FILE:imago-c>" "${IMAGO_DLL_DIR}/"
            COMMAND "${Java_JAR_EXECUTABLE}" "uf" "${imago_jar_filename}" "com"
            WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR})

    add_custom_command(TARGET imago-java POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E make_directory ${IMAGO_DIST_DIR}
            COMMAND "${CMAKE_COMMAND}" "-E" "copy" "${imago_jar_filename}" "${IMAGO_DIST_DIR}/"
            WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR})
endif()

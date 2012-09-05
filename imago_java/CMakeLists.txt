set(CMAKE_JAVA_INCLUDE_PATH lib/jna.jar)
set(CMAKE_JAVA_TARGET_OUTPUT_NAME imago)

file(GLOB_RECURSE Imago_java_SRC RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} src/*.java)
add_jar(imago_java ${Imago_java_SRC})
add_dependencies(imago_java imago_c_shared)

#Add manifest
get_target_property(imago_jar_filename imago_java JAR_FILE)
add_custom_command(TARGET imago_java POST_BUILD
				   COMMAND "${Java_JAR_EXECUTABLE}" "ufm" "${imago_jar_filename}" "manifest.mf"
				   WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

#Add libraries
get_target_property(imago_dll_filename imago_c_shared LOCATION)
set(IMAGO_DLL_DIR "com/ggasoftware/imago/${SYSTEM_NAME}/${SUBSYSTEM_NAME}")
add_custom_command(TARGET imago_java POST_BUILD
	               COMMAND "${CMAKE_COMMAND}" "-E" "make_directory" "${IMAGO_DLL_DIR}"
	               WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR})

set(CMAKE_INSTALL_SYSTEM_RUNTIME_LIBS_SKIP TRUE)
include(InstallRequiredSystemLibraries)
foreach(lib ${CMAKE_INSTALL_SYSTEM_RUNTIME_LIBS})
	add_custom_command(TARGET imago_java POST_BUILD
	                   COMMAND "${CMAKE_COMMAND}" "-E" "copy" "${lib}" "${IMAGO_DLL_DIR}/"	
	                   WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR})
endforeach()

add_custom_command(TARGET imago_java POST_BUILD
	               COMMAND "${CMAKE_COMMAND}" "-E" "copy" "${imago_dll_filename}" "${IMAGO_DLL_DIR}/"
				   COMMAND "${Java_JAR_EXECUTABLE}" "uf" "${imago_jar_filename}" "com"
				   WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR})

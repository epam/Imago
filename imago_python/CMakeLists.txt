find_package(Python3 COMPONENTS Interpreter REQUIRED)

if(NOT Python3_FOUND)
	message(WARNING "Python executable not found, imago-python could not be built")
else()
	file(TO_NATIVE_PATH ${CMAKE_CURRENT_SOURCE_DIR} NATIVE_CURRENT_SOURCE_DIR)
	file(TO_NATIVE_PATH ${IMAGO_DIST_DIR} IMAGO_NATIVE_DIST_DIR)
	message(STATUS "${IMAGO_DIST_DIR} ${IMAGO_NATIVE_DIST_DIR}")
	add_custom_target(imago_python ALL
			COMMAND ${CMAKE_COMMAND} -E remove_directory ${CMAKE_CURRENT_SOURCE_DIR}/imago/lib/${IMAGO_SYSTEM_NAME_LOWER}-${IMAGO_SYSTEM_PROCESSOR_LOWER}
			COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_CURRENT_SOURCE_DIR}/imago/lib/${IMAGO_SYSTEM_NAME_LOWER}-${IMAGO_SYSTEM_PROCESSOR_LOWER}
			COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:imago_c_shared> ${CMAKE_CURRENT_SOURCE_DIR}/imago/lib/${IMAGO_SYSTEM_NAME_LOWER}-${IMAGO_SYSTEM_PROCESSOR_LOWER}/
			COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:indigo> ${CMAKE_CURRENT_SOURCE_DIR}/imago/lib/${IMAGO_SYSTEM_NAME_LOWER}-${IMAGO_SYSTEM_PROCESSOR_LOWER}/
			COMMAND ${Python3_EXECUTABLE} setup.py test
			COMMAND ${Python3_EXECUTABLE} setup.py bdist_wheel --plat-name=macosx_10_7_intel
			COMMAND ${Python3_EXECUTABLE} setup.py bdist_wheel --plat-name=manylinux1_x86_64
			COMMAND ${Python3_EXECUTABLE} setup.py bdist_wheel --plat-name=manylinux1_i686
			COMMAND ${Python3_EXECUTABLE} setup.py bdist_wheel --plat-name=win_amd64
			COMMAND ${Python3_EXECUTABLE} setup.py bdist_wheel --plat-name=win32
			COMMAND ${Python3_EXECUTABLE} setup.py bdist_wheel --plat-name=mingw
			COMMAND ${CMAKE_COMMAND} -E make_directory ${IMAGO_DIST_DIR}
			COMMAND ${COPY_COMMAND} ${NATIVE_CURRENT_SOURCE_DIR}${SEP}dist${SEP}*.whl ${IMAGO_NATIVE_DIST_DIR}${SEP}
			DEPENDS imago_c_shared
			WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
	)
endif()

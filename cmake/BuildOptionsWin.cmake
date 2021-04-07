add_definitions("/D _CRT_SECURE_NO_DEPRECATE /D BOOST_ALL_NO_LIB")

if(MSVC)
	string(APPEND CMAKE_C_FLAGS " -MP")
	string(APPEND CMAKE_CXX_FLAGS " -MP")
endif()

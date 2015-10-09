if(SYSTEM_NAME STREQUAL "Win")
	include(BuildOptionsWin)
elseif(SYSTEM_NAME STREQUAL "Linux")
	include(BuildOptionsLinux)
elseif(SYSTEM_NAME STREQUAL "Mac")
	include(BuildOptionsMac)
endif()

set(THIRD_PARTY_DIR ${CMAKE_SOURCE_DIR}/third_party)

find_package(Java)

set(CMAKE_INSTALL_SYSTEM_RUNTIME_LIBS_SKIP TRUE)
include(InstallRequiredSystemLibraries)

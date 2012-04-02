project(BeerMat)

set(BEERMAT_VERSION "1.1.24.1")

cmake_policy(SET CMP0015 NEW)
cmake_policy(SET CMP0016 NEW)

file(GLOB hdrs *.h Classes/*.h)
file(GLOB srcs_m *.m Classes/*.m)
file(GLOB srcs_mm *.mm Classes/*.mm)

file(GLOB icons ireco*.png reaxys.png Entitlements.plist)
file(GLOB xibs *.xib iPad/*.xib ../tests/data/ff.font)
file(GLOB_RECURSE ketcher Ketcher/*)
file(GLOB ketcher_excl Ketcher/ketcher*.py Ketcher/ketcher.html Ketcher/*.sh Kecher/ios/.DS_Store)
file(GLOB_RECURSE ketcher_excl_rec Ketcher/mol/* Ketcher/molfiles/* Ketcher/nbproject/* Ketcher/.git/* Ketcher/.idea/*)
list(REMOVE_ITEM ketcher ${ketcher_excl})
list(REMOVE_ITEM ketcher ${ketcher_excl_rec})

set(RESOURCES ${xibs} ${icons} ${ketcher})

#link_directories(\${HOME}/\${SDKROOT}/lib)
include_directories(${Boost_INCLUDE_DIR})
include_directories(${INDIGO_INCLUDE_DIR})
include_directories(${OpenCV_INCLUDE_DIRS})
include_directories(../imago/src)
include_directories(.)

set(APP_TYPE MACOSX_BUNDLE)

set_source_files_properties(${srcs_m} PROPERTIES LANGUAGE C COMPILE_FLAGS "-x objective-c")
set_source_files_properties(${srcs_mm} PROPERTIES LANGUAGE C COMPILE_FLAGS "-x objective-c++")

add_executable(${PROJECT_NAME}
    ${APP_TYPE}
    ${hdrs}
    ${srcs_m}
	${srcs_mm}
	${RESOURCES}
)

target_link_libraries(${PROJECT_NAME} imago
	 "-framework Foundation -framework MessageUI -framework AudioToolbox -framework CoreGraphics -framework QuartzCore -framework UIKit")

# code signing
set_target_properties(${PROJECT_NAME} PROPERTIES 
	RESOURCE "${RESOURCES}"
	XCODE_ATTRIBUTE_CODE_SIGN_IDENTITY "iPhone Developer"
	MACOSX_BUNDLE_BUNDLE_NAME "\${PRODUCT_NAME}"
	MACOSX_BUNDLE_GUI_IDENTIFIER "6KBW792M89.com.ggasoftware.\${PRODUCT_NAME:rfc1034identifier}"
	MACOSX_BUNDLE_INFO_PLIST ${CMAKE_CURRENT_SOURCE_DIR}/BeerMat-cmake-Info.plist
#TODO: Not working yet [variant=Release]
	XCODE_ATTRIBUTE_CODE_SIGN_ENTITLEMENTS ${CMAKE_CURRENT_SOURCE_DIR}/Entitlements.plist
	XCODE_ATTRIBUTE_IPHONEOS_DEPLOYMENT_TARGET 4.2
	XCODE_ATTRIBUTE_TARGETED_DEVICE_FAMILY "1,2"
	XCODE_ATTRIBUTE_SKIP_INSTALL NO
	XCODE_ATTRIBUTE_INSTALL_PATH "/Application"

	#    XCODE_ATTRIBUTE_GCC_FAST_MATH YES
    XCODE_ATTRIBUTE_GCC_INLINES_ARE_PRIVATE_EXTERN YES
    XCODE_ATTRIBUTE_GCC_SYMBOLS_PRIVATE_EXTERN YES
#    XCODE_ATTRIBUTE_GCC_THUMB_SUPPORT NO
	)
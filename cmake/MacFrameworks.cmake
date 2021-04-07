set(FRAMEWORK_PATH /Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/System/Library/Frameworks)

macro(ADD_FRAMEWORK fwname appname)
    set(FRAMEWORK_${fwname} ${FRAMEWORK_PATH}/${fwname}.framework)

    if(NOT IS_DIRECTORY ${FRAMEWORK_${fwname}})
        message(ERROR ": Framework ${fwname} not found")
    else()
        target_link_libraries(${appname} ${FRAMEWORK_${fwname}})
        message(STATUS "Framework ${fwname} found at ${FRAMEWORK_${fwname}}")
    endif()
endmacro()

macro(FIND_FRAMEWORK fwname)
    set(FRAMEWORK_${fwname} ${FRAMEWORK_PATH}/${fwname}.framework)

    if(NOT IS_DIRECTORY ${FRAMEWORK_${fwname}})
        message(ERROR ": Framework ${fwname} not found")
    else()
        message(STATUS "Framework ${fwname} found at ${FRAMEWORK_${fwname}}")
    endif()
endmacro()

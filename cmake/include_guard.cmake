# Include guard (include_guard is not included in older cmake version)
# Optionally; pass in the name of the include guard
macro(INCLUDE_GUARD_X)

    set(GUARD_NAME ${ARGV0})
    if (NOT GUARD_NAME)
        file(RELATIVE_PATH GUARD_NAME "${PROJECT_SOURCE_DIR}" "${CMAKE_CURRENT_LIST_FILE}")
    endif()

    GET_PROPERTY(GUARD_VALUE GLOBAL PROPERTY ${GUARD_NAME})

    if(GUARD_VALUE)
        return()
    endif()

    SET_PROPERTY(GLOBAL PROPERTY ${GUARD_NAME} TRUE)

endmacro(INCLUDE_GUARD_X)
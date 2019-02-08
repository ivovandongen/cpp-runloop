include_guard_x()

set(LIBCDS_DIR ${CMAKE_SOURCE_DIR}/deps/libcds)

add_library(libcds INTERFACE)

target_include_directories(libcds
        SYSTEM INTERFACE ${LIBCDS_DIR}
        )
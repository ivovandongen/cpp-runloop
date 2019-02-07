include_guard_x()

set(ASIO_DIR ${CMAKE_SOURCE_DIR}/deps/asio/asio)

add_library(asio INTERFACE)

target_include_directories(asio
        SYSTEM INTERFACE ${ASIO_DIR}/include
        )
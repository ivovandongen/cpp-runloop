git_include(libcds)

find_package(Boost 1.53 COMPONENTS thread REQUIRED)

get_filename_component(EXECUTABLE ${CMAKE_CURRENT_SOURCE_DIR} NAME)

add_executable(${EXECUTABLE}
        main.cpp
        runloop.cpp
        )

target_include_directories(${EXECUTABLE}
        PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}
        )

target_link_libraries(${EXECUTABLE} PRIVATE libcds Boost::thread)

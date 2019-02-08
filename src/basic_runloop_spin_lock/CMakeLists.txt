get_filename_component(EXECUTABLE ${CMAKE_CURRENT_SOURCE_DIR} NAME)

add_executable(${EXECUTABLE}
        main.cpp
        runloop.cpp
        )

target_include_directories(${EXECUTABLE}
        PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}
        )

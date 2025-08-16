cmake_minimum_required(VERSION 3.31)
project(untitled C)

set(CMAKE_C_STANDARD 23)

add_executable(untitled src/main.c
        include/file_io.h
        include/utils.h
        src/book.c
        src/utils.c
        src/file_io.c
        include/config.h)

add_custom_command(TARGET untitled POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/data $<TARGET_FILE_DIR:untitled>/data
)

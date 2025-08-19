cmake_minimum_required(VERSION 3.31)
project(untitled C)

set(CMAKE_C_STANDARD 23)

# ---- Configure BOOKS_FILE path ----
# Always point to data/books.txt relative to the binary
set(BOOKS_FILE "data/books.txt")

configure_file(
        ${CMAKE_SOURCE_DIR}/include/config.h.in
        ${CMAKE_BINARY_DIR}/config.h
        @ONLY
)

# ---- Build target ----
add_executable(untitled
        src/main.c
        src/book.c
        src/utils.c
        src/file_io.c
        include/file_io.h
        include/utils.h
)

# Tell compiler to look for headers in include/ and the build dir
target_include_directories(untitled PRIVATE
        ${CMAKE_SOURCE_DIR}/include
        ${CMAKE_BINARY_DIR}
)

# ---- Copy data folder for local builds (CLion, etc.) ----
add_custom_command(TARGET untitled POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/data
        $<TARGET_FILE_DIR:untitled>/data
)

# ---- Install rules ----
install(TARGETS untitled
        RUNTIME DESTINATION bin)

install(DIRECTORY ${CMAKE_SOURCE_DIR}/data
        DESTINATION bin)

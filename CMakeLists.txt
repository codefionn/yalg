cmake_minimum_required(VERSION 3.1)
project(yalg)

set(yalg_SOURCES "${yalg_SOURCE_DIR}/src/lexer.c")

add_executable(yalg "${yalg_SOURCE_DIR}/src/main.c"
                    ${yalg_SOURCES})
target_include_directories(yalg PUBLIC "${yalg_SOURCE_DIR}/include")

add_subdirectory("${yalg_SOURCE_DIR}/test")

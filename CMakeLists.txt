cmake_minimum_required(VERSION 3.1)
project(yalg)

add_executable(yalg "${yalg_SOURCE_DIR}/src/main.c"
                    "${yalg_SOURCE_DIR}/src/lexer.c")
target_include_directories(yalg PUBLIC "${yalg_SOURCE_DIR}/include")

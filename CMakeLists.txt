cmake_minimum_required(VERSION 3.1)
project(yalg)

add_executable(yalg "${yalg_SOURCE_DIR}/src/main.cpp")
target_include_directories(yalg "${yalg_SOURCE_DIR}/include")

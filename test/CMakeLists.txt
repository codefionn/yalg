include(CTest)
enable_testing()

# lexer
add_executable(lexer "${yalg_SOURCE_DIR}/test/lexer.c"
                     ${yalg_SOURCES})
target_include_directories(lexer PUBLIC "${yalg_SOURCE_DIR}/include")
add_test(lexer0 lexer "text" "id")
add_test(lexer1 lexer "text" "[0-9a-zA-Z]")

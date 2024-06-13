flex_target(lexer lexer.ll ${CMAKE_CURRENT_BINARY_DIR}/lexer.cpp)
bison_target(parser parser.yy ${CMAKE_CURRENT_BINARY_DIR}/parser.cpp COMPILE_FLAGS "-d -v")

add_library(ParserLib STATIC "${CMAKE_CURRENT_BINARY_DIR}/lexer.cpp" "${CMAKE_CURRENT_BINARY_DIR}/parser.cpp" location_range.cpp)

add_flex_bison_dependency(lexer parser)


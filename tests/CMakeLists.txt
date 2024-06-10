set(TARGET tree_tests) 

add_executable(${TARGET} tree_tests.cpp)
set_property(TARGET ${TARGET} PROPERTY CXX_STANDARD 20)

target_compile_options(${TARGET} PUBLIC "-fconcepts-diagnostics-depth=4")

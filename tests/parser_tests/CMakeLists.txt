set(TARGET parser_tests) 

enable_testing()

add_executable(${TARGET} parser_tests.cpp)
set_property(TARGET ${TARGET} PROPERTY CXX_STANDARD 20)

target_link_libraries(${TARGET} GTest::gtest_main)

include(GoogleTest)
gtest_discover_tests(${TARGET})


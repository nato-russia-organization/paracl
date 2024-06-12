cmake_policy(SET CMP0048 NEW)
project(paracl VERSION 0.1)

cmake_minimum_required(VERSION 3.20)
set(CXX_STANDARD_REQUIRED ON)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

find_package(FLEX)
find_package(BISON)

add_compile_options("-std=c++20")

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
FetchContent_MakeAvailable(googletest)

include_directories(${PROJECT_SOURCE_DIR}/build/src/flex_bison_sources)
include_directories(${PROJECT_SOURCE_DIR}/inc)
add_subdirectory(src)
add_subdirectory(tests)

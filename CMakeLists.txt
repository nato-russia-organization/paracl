project(paracl)

cmake_minimum_required(VERSION 3.20)
set(CXX_STANDARD_REQUIRED ON)

find_package(FLEX)
find_package(BISON)

include_directories(${PROJECT_SOURCE_DIR}/inc)
add_subdirectory(src)
add_subdirectory(tests)

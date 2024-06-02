set(TARGET tree)

add_library(${TARGET} tree.cpp)
set_property(TARGET ${TARGET} PROPERTY CXX_STANDARD 20)

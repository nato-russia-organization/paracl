set(TARGET paracli)

add_executable(${TARGET} paracli.cpp)

target_link_libraries(${TARGET} PUBLIC ParserLib)

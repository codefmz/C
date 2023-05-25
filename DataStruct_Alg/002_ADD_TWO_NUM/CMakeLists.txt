cmake_minimum_required(VERSION 3.0)

project(AddTwoNum)

include_directories(include)

add_subdirectory(src)

set(SOURCES main.c)

add_executable(addTwoNum ${SOURCES})

target_link_libraries(addTwoNum PRIVATE src)
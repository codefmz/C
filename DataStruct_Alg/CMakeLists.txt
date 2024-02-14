cmake_minimum_required(VERSION 3.5.0)
project(DataStruct VERSION 0.1.0)

set(CMAKE_C_FLAGS "-g -std=c99 -pthread ${CMAKE_C_FLAGS}")
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")

include_directories(
    ${PROJECT_SOURCE_DIR}/include
    ${PROJECT_SOURCE_DIR}/include/gtest
    ${PROJECT_SOURCE_DIR}/include/util
)

add_subdirectory(src/DataStruct)

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)

link_directories(
    ${PROJECT_SOURCE_DIR}/lib
    ${PROJECT_SOURCE_DIR}/lib/util/
    ${PROJECT_SOURCE_DIR}/lib/gtest/
)

enable_testing()

add_executable(ringbuffer_test test/DataStruct/ringbuffer_test.cc)
target_link_libraries(ringbuffer_test rb_static util_static gtest_main gtest)
add_custom_command(TARGET ringbuffer_test
    COMMAND echo "target ringbuffer"
)
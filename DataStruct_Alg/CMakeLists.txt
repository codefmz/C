cmake_minimum_required(VERSION 3.5.0)
project(DataStruct VERSION 0.1.0)

set(CMAKE_C_FLAGS "-g -std=c99 -Wunused-variable -pthread ${CMAKE_C_FLAGS}")
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -pthread")

include_directories(
    ${PROJECT_SOURCE_DIR}/include
    ${PROJECT_SOURCE_DIR}/include/gtest
    ${PROJECT_SOURCE_DIR}/include/util
)

add_subdirectory(src/DataStruct)

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)

set(TestDir test/DataStruct)

link_directories(
    ${PROJECT_SOURCE_DIR}/lib
    ${PROJECT_SOURCE_DIR}/lib/util/
    ${PROJECT_SOURCE_DIR}/lib/gtest/
)

enable_testing()

#ringbuffer
add_executable(ringbuffer_test ${TestDir}/ringbuffer_test.cc)
target_link_libraries(ringbuffer_test rb_static util_static gtest_main gtest)
add_custom_command(TARGET ringbuffer_test
    COMMAND echo "compile ring buffer test..."
)

#radixtree
add_executable(radixtree ${TestDir}/radixtree_test.cc)
target_link_libraries(radixtree rt_static util_static gtest_main gtest)
add_custom_command(TARGET radixtree
    PRE_BUILD
    COMMAND echo "compile radix tree test..."
)

#binarytree
add_executable(binarytree ${TestDir}/binarytree_test.cc)
target_link_libraries(binarytree bt_static util_static gtest_main gtest)
add_custom_command(TARGET binarytree
    PRE_BUILD
    COMMAND echo "compile binary tree test..."
)
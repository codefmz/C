cmake_minimum_required(VERSION 3.5.0)
project(DataStruct VERSION 0.1.0)

set(CMAKE_C_FLAGS
    "-g"
    "-o"
    "-std=c11"
    "-Wunused"
    "-variable"
    "-pthread"
)

set(CMAKE_CXX_FLAGS
    "-g -pthread"
)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


include_directories(
    ${PROJECT_SOURCE_DIR}/include
)

add_subdirectory(src/DataStruct)

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)

set(TestDir test/DataStruct)
set(TEST_LIB
    util_static
    gtest_main
    gtest
)

link_directories(
    ${PROJECT_SOURCE_DIR}/lib
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

#gcc_compile
add_executable(gccC ${PROJECT_SOURCE_DIR}/test/Other/gcc_compile.cc)
target_link_libraries(gccC util_static gtest_main gtest)
add_custom_command(TARGET gccC
    PRE_BUILD
    COMMAND echo "compile gccC test..."
)

#monotonic_stack
add_executable(monStack ${PROJECT_SOURCE_DIR}/test/Arithmetic/monotonic_stack.cc)
target_link_libraries(monStack util_static gtest_main gtest)
add_custom_command(TARGET gccC
    PRE_BUILD
    COMMAND echo "compile monStack test..."
)

#unset
add_executable(unset ${PROJECT_SOURCE_DIR}/test/Arithmetic/unset.cc)
target_link_libraries(unset util_static gtest_main gtest)
add_custom_command(TARGET gccC
    PRE_BUILD
    COMMAND echo "compile unset test..."
)
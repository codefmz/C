# 设置最低的CMake版本要求
cmake_minimum_required(VERSION 3.5)

# 设置项目名称
project(MyProject)

# 设置编译器选项，例如编译标准
set(CMAKE_C_STANDARD 11)

set(UTIL ../../Util/include)



set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -g")

# set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# # 添加头文件目录
# include_directories(${UTIL})
# include_directories(${LISTINCLUDE})


# # 收集源文件
# set(LISTTESTFILE ./DataStruct/list_test.c)

# set(STACKTESTFILE ./DataStruct/stack_test.c)

set(012_intToRoman ../../src/LeetCode/012_intToRoman/intToRoman.c)

# 生成可执行文件
add_executable(intToRoman ${012_intToRoman})

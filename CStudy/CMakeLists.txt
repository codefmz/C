# 设置最低的CMake版本要求
cmake_minimum_required(VERSION 3.5)

# 设置项目名称
project(MyProject)

# 设置编译器选项，例如编译标准
set(CMAKE_C_STANDARD 11)

# 添加头文件目录
include_directories(include)

# 收集源文件
set(SOURCES
    main.c
)

# 生成可执行文件
add_executable(CStudy ${SOURCES})
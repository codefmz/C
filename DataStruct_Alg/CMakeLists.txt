cmake_minimum_required(VERSION 3.5.0)
project(DataStruct VERSION 0.1.0)

set(CMAKE_C_FLAGS "-g -std=c99 -pthread ${CMAKE_C_FLAGS}")

add_subdirectory(src/DataStruct)
add_subdirectory(test)
# add_subdirectory(../Util)
set(target_project_name ${VAR_NAME})
set(target_exe_name "${VAR_NAME}_exe")
set(SRC "${target_project_name}_src")
message("target_project_name = ${target_project_name} SRC = ${SRC}")
get_property(SRC GLOBAL PROPERTY ${SRC}) #获取全局的属性
get_property(tree_include GLOBAL PROPERTY "tree_include") #获取全局的属性
get_property(list_include GLOBAL PROPERTY "list_include")


message("list_include = ${list_include}")

include_directories(
    ./config
    ../Util/include
    ${tree_include}
    ${list_include}
)

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
add_executable(${target_exe_name} ${SRC})

add_custom_target(${target_project_name}
    COMMAND echo "build ${target_project_name} start..."
    COMMAND rm -rf ./${target_project_name}
    COMMAND ${CMAKE_COMMAND} --build ${CMAKE_BINARY_DIR} --target ${target_exe_name}
    COMMAND cp ../bin/${target_project_name} ../${target_project_name}
    COMMAND echo "build ${target_project_name} end..."
)

add_custom_target(cls
    COMMAND rm -rf ./* ../bin/*
)

#如果变量定义过，则不处理，如果未定义过，则设置默认值 “option” 是一个描述符
# option(USE_MY_STATIC_OUT "option" ON)

# target_link_libraries(${PROJECT_NAME} out_static self_static_lib self_dynamic_dll)

#如果变量定义过，则不处理，如果未定义过，则设置默认值 “option” 是一个描述符
option(USE_MY_PRIORITY_QUEUE "option" OFF)

configure_file (
    "${PROJECT_SOURCE_DIR}/config/config.h.in"
    "${PROJECT_SOURCE_DIR}/config/config_my.h"
)

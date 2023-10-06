cmake_minimum_required(VERSION 3.5.0)
project(CMakeProgram VERSION 0.1.0)


set(CMAKE_CXX_FLAGS "-g -std=c++11 ${CMAKE_CXX_FLAGS}")

#message("PROJECT_SOUCE_DIR = " ${PROJECT_SOURCE_DIR})
# message("CMAKE_CXX_FLAGS = " ${CMAKE_CXX_FLAGS})

include_directories(./out_include
                    ./self_static/self_static_add/include
                    ./self_static/self_static_sub/include
                    ./self_dynamic/self_dynamic_div/include
                    ./self_dynamic/self_dynamic_mul/include
                    ./config
)

##[[
add_subdirectory(self_static)
add_subdirectory(self_dynamic)
add_subdirectory(out_src)

link_directories(./out_static ./out_dynamic)

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)

add_executable(${PROJECT_NAME} main.cpp)


option(USE_MY_STATIC_OUT "option" ON) #如果变量定义过，则不处理，如果未定义过，则设置默认值 “option” 是一个描述符
option(TEST_CMAKE_DEFINE_OFF_EFFECT "comment" OFF)
set(TEST_VARIABLE_VALUE "\"TEST_VARIABLE_NAME IS WAHAHA\"")

configure_file (
    "${PROJECT_SOURCE_DIR}/config/config.h.in"
    "${PROJECT_SOURCE_DIR}/config/config_my89757.h"
)

message("USE_MY_STATIC_OUT = :" ${USE_MY_STATIC_OUT} "CMAKE_INSTALL_PREFIX = " ${CMAKE_INSTALL_PREFIX})

if(${USE_MY_STATIC_OUT} STREQUAL "ON")
target_link_libraries(${PROJECT_NAME} out_static self_static_lib self_dynamic_dll)
else()
target_link_libraries(${PROJECT_NAME} out_dynamic self_static_lib self_dynamic_dll)
endif()
#]]

# add_library(total_dll SHARED out_static self_static_lib self_dynamic_dll)
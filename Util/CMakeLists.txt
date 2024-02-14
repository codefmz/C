cmake_minimum_required(VERSION 3.5.0)
project(DataStruct VERSION 0.1.0)

aux_source_directory(./src LOG_SRC)

include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/build/lib/)
add_library(util_static STATIC ${LOG_SRC})
# add_custom_command(TARGET util_static
#     PRE_BUILD
#     COMMAND echo "ln -s util header"
#     COMMAND mkdir ${PROJECT_SOURCE_DIR}/include/util
#     COMMAND ln -s ${CMAKE_CURRENT_SOURCE_DIR}/include/* ${PROJECT_SOURCE_DIR}/include/util/
# )
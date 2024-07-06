cmake_minimum_required(VERSION 3.5.0)
project(DataStruct VERSION 0.1.0)

aux_source_directory(./src UTIL_SRC)

set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib/)
add_library(util_static STATIC ${UTIL_SRC})
target_include_directories(util_static
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)
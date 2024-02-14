aux_source_directory(./src RB_SRC)

include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${PROJECT_SOURCE_DIR}/include/
    ${PROJECT_SOURCE_DIR}/include/util
)


# file(GLOB_RECURSE header "include/*.h")
# message("header = ${header}")

set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib)

add_library(rb_static STATIC ${RB_SRC})
# target_link_libraries(rb_static PRIVATE util_static)
# link_directories(
#     ${PROJECT_SOURCE_DIR}/lib/util
# )
add_custom_command(TARGET rb_static
    PRE_BUILD
    COMMAND echo "ln -s include rb_static_lib"
    COMMAND cp ${CMAKE_CURRENT_SOURCE_DIR}/include/* ${PROJECT_SOURCE_DIR}/include/
)
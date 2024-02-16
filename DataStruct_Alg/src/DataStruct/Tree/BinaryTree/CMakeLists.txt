aux_source_directory(./src BT_SRC)

include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${PROJECT_SOURCE_DIR}/include/
    ${PROJECT_SOURCE_DIR}/include/util
)

set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib)

add_library(bt_static STATIC ${BT_SRC})
add_custom_command(TARGET bt_static
    PRE_BUILD
    COMMAND echo "compile binarytree static!"
    COMMAND cp ${CMAKE_CURRENT_SOURCE_DIR}/include/* ${PROJECT_SOURCE_DIR}/include/
)
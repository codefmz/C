add_subdirectory(List)
add_subdirectory(Tree)

# get_property(LIST_DYNAMIC GLOBAL PROPERTY "LIST_SRC_FILE_INNER") #获取全局的属性
# get_property(TREE_DYNAMIC GLOBAL PROPERTY "TREE_SRC_FILE_INNER")

# include_directories(
#             ./List
#             ./Tree
# )
# set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)

#这个模块构建生成一个动态库, SHARED 就表示一个动态库
# add_library(dataStruct SHARED ${LIST_DYNAMIC} ${TREE_DYNAMIC})
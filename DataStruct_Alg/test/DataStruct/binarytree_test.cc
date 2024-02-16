#include "base.h"
#include "binarytree.h"
#include "log.h"
#include "gtest/gtest.h"
#include <stdio.h>
#include <stdlib.h>

uint32_t g_valueTotal[12] = { 7, 3, 15, 1, 5, 11, 21, 6, 13, 19, 23, 0 };
uint32_t g_valueTotal_1[12] = { 7, 3, 15, 5, 11, 21, 6, 13, 19, 23, 0 };
uint32_t g_valueTotal_2[12] = { 7, 3, 15, 1, 6, 11, 21, 13, 19, 23, 0 };
uint32_t g_realValue[12] = { 0 };
uint32_t g_index = 0;

uint32_t TraversePrintAndSet(uint32_t value)
{
    printf("\t%u", value);
    g_realValue[g_index++] = value;

    return OK;
}

TEST(binarytree, func1)
{
    BinaryTree* tree;
    uint32_t ret, i;

    tree = BinaryTreeCreate();

    BinaryTreeInsert(tree, 7);
    BinaryTreeInsert(tree, 3);
    BinaryTreeInsert(tree, 15);
    BinaryTreeInsert(tree, 1);
    BinaryTreeInsert(tree, 5);
    BinaryTreeInsert(tree, 6);
    BinaryTreeInsert(tree, 11);
    BinaryTreeInsert(tree, 21);
    BinaryTreeInsert(tree, 13);
    BinaryTreeInsert(tree, 19);
    BinaryTreeInsert(tree, 23);

    printf("value = ");
    BinaryTreeTraverse(tree, TraversePrintAndSet);
    for (i = 0; i < g_index; ++i) {
        EXPECT_EQ(g_realValue[i], g_valueTotal[i]);
    }
    g_index = 0;

    ret = BinaryTreeFind(tree, 19);
    EXPECT_EQ(ret, OK);
    ret = BinaryTreeFind(tree, 23);
    EXPECT_EQ(ret, OK);
    ret = BinaryTreeFind(tree, 18);
    EXPECT_EQ(ret, ERROR);

    ret = BinaryTreeErase(tree, 1);
    EXPECT_EQ(ret, OK);
    printf("value1 = ");
    BinaryTreeTraverse(tree, TraversePrintAndSet);
    for (i = 0; i < g_index; ++i) {
        EXPECT_EQ(g_realValue[i], g_valueTotal_1[i]);
    }
    g_index = 0;
    BinaryTreeInsert(tree, 1);

    ret = BinaryTreeErase(tree, 5);
    EXPECT_EQ(ret, OK);
    printf("value1 = ");
    BinaryTreeTraverse(tree, TraversePrintAndSet);
    for (i = 0; i < g_index; ++i) {
        EXPECT_EQ(g_realValue[i], g_valueTotal_2[i]);
    }
    g_index = 0;

    ret = BinaryTreeErase(tree, 11);
    EXPECT_EQ(ret, OK);
    printf("value1 = ");
    BinaryTreeTraverse(tree, TraversePrintAndSet);
    g_index = 0;

    ret = BinaryTreeErase(tree, 21);
    EXPECT_EQ(ret, OK);
    printf("value1 = ");
    BinaryTreeTraverse(tree, TraversePrintAndSet);
    g_index = 0;

    BinaryTreeDelete(tree);
}
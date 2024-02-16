#include "base.h"
#include "log.h"
#include "radixtree.h"
#include "gtest/gtest.h"
#include <stdio.h>
#include <stdlib.h>

TEST(radixtree, func1)
{
    void* tree;
    int a = 1, b = 2, c = 3, d = 0;
    uintptr_t ptr = 0;
    int ret;

    tree = RadixTreeCreate32(0);
    ret = RadixTreeInsert32(tree, 1, (uintptr_t)&a);
    EXPECT_EQ(ret, OK);
    ret = RadixTreeInsert32(tree, 2, (uintptr_t)&b);
    EXPECT_EQ(ret, OK);
    ret = RadixTreeInsert32(tree, 3, (uintptr_t)&c);
    EXPECT_EQ(ret, OK);

    ptr = RadixTreeFind32(tree, 1);
    EXPECT_EQ(ptr, (uintptr_t)&a);

    ptr = RadixTreeFind32(tree, 2);
    EXPECT_EQ(ptr, (uintptr_t)&b);

    ret = RadixTreeDelete32(tree, 3);
    EXPECT_EQ(ret, OK);

    ptr = RadixTreeFind32(tree, 3);
    EXPECT_EQ(ptr, INVALID_VALUE);

    ret = RadixTreeDestory32(tree);
    EXPECT_EQ(ret, OK);
}
#include "errno.h"
#include "log.h"
#include "gtest/gtest.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <vector>

using namespace std;

typedef struct {
    int size;
    int root;
    int* array;
} UnSet;

UnSet* CreateUnset(int size)
{
    UnSet* set = (UnSet*)malloc(sizeof(UnSet));
    set->size = size;
    set->root = 0;
    set->array = (int*)malloc(size * sizeof(int));
    memset(set->array, 0, size * sizeof(int));
    for (uint32_t i = 0; i < size; i++) {
        set->array[i] = -1;
    }

    return set;
}

int FindRoot(UnSet* set, int x)
{
    if (set->array[x] < 0) {
        return x;
    }

    return FindRoot(set, set->array[x]);
}

bool UnionSet(UnSet* set, int x, int y)
{
    x = FindRoot(set, x);
    y = FindRoot(set, y);
    if (x == y) {
        return false;
    }

    if (set->array[x] < set->array[y]) {
        set->array[y] = x;
    } else {
        if (set->array[x] == set->array[y]) {
            --set->array[y];
        }
        set->array[x] = y;
    }

    return true;
}

void DestoryUnSet(UnSet* set)
{
    free(set->array);
    set->array = NULL;
    free(set);
}

int findCircleNum(int** isConnected, int isConnectedSize, int* isConnectedColSize)
{
    UnSet* set = CreateUnset(isConnectedSize);

    for (int i = 0; i < isConnectedSize; ++i) {
        for (int j = 0; j < i; ++j) {
            if (isConnected[i][j] == 1) {
                UnionSet(set, i, j);
            }
        }
    }

    int num = 0;
    for (int i = 0; i < isConnectedSize; ++i) {
        if (set->array[i] < 0) {
            ++num;
        }
    }

    return num;
}

// 力扣547
TEST(UNSET, province_num)
{
    int isConnected[3][3] = {
        { 1, 1, 0 },
        { 1, 1, 0 },
        { 0, 0, 1 }
    };
    int arrLen = 3;

    int** p = (int**)malloc(sizeof(int*) * arrLen);
    for (int i = 0; i < arrLen; ++i) {
        p[i] = (int*)malloc(sizeof(int) * arrLen);
        memcpy(p[i], isConnected[i], arrLen * sizeof(int));
    }
    int num = findCircleNum(p, 3, NULL);
    EXPECT_EQ(2, num);
}

// 力扣684
#include "errno.h"
#include "log.h"
#include "gtest/gtest.h"
#include <stdio.h>
#include <stdlib.h>
#include <vector>

using namespace std;
// 单调栈：三个特定
// 1. 栈种元素具有单调性
// 2. 在遍历的时候可以找到第一个比它小的元素或第一个比它大的元素

/*
问题1：给定一个数组，输出相同大小的数组， 输出数组的每个元素满足如下规则“
1、数组中地i个元素为，元素组中第i个元素到后面大于元素组的距离，如果后面没有大于原数组的值，则该值为-1
例子：
input: 5, 3, 1, 2, 4
output: -1, 3, 1, 1, -1
*/

/*
解法思路：
{0} [-1, -1, -1, -1, -1]
{0, 1} [-1, -1, -1, -1, -1]
{0, 1, 2} [-1, -1, -1, -1, -1]
{0, 1, 2, 3} => 把所有小于2的值pop出来，按照pop次数给对应索引置位（必须要保证之前没有设置过）
=> 将所有的东西放回到栈中 => [-1, -1, 1, -1, -1]
{0, 1, 2, 3, 4} [-1, 3, 1, 1, -1]
*/
TEST(MonStack, array_greater_index_test1)
{
    int array[] = { 5, 3, 1, 2, 4 };
    const int expOutput[5] = { -1, 3, 1, 1, -1 }; /*预计结果*/
    int output[5] = { -1, -1, -1, -1, -1 };
    int monStackIndex = 0;
    int arrLen = 5;
    int i, j;

    for (i = 1; i < arrLen; i++) {
        for (j = monStackIndex; j > 0; --j) {
            if (array[j] >= array[i]) {
                break;
            }

            if (output[j] == -1) {
                output[j] = monStackIndex - j + 1;
            }
        }
        monStackIndex = i;
    }

    for (i = 0; i < arrLen; ++i) {
        EXPECT_EQ(output[i], expOutput[i]);
    }
}

/* 力扣第84题
问题2：给定 n 个非负整数，用来表示柱状图中各个柱子的高度。每个柱子彼此相邻，且宽度为 1 求在该柱状图中，能够勾勒出来的矩形的最大面积。
例子：heights = [2,1,5,6,2,3]， maxRectArea = 10;
*/
/*
解法思路：记录以指定点为高的最大面积，当它出现一个比单调增队列小的值时，那么此时以它为高的面积可以确定，
此时宽度为右边的索引减去左边栈的索引
stack:{0}           heightArea[0, 0, 0, 0, 0, 0]
stack:{1}           heightArea[2, 0, 0, 0, 0, 0]
stack:{1, 2, 3}     heightArea[2, 0, 0, 0, 0, 0]
stack:{1, 4}        heightArea[2, 0, 10, 6, 0, 0]
stack:{1, 4, 5}     heightArea[2, 0, 10, 6, 0, 0]
stack:{1, 4}        heightArea[2, 0, 10, 6, 0, 3]
stack:{1}           heightArea[2, 0, 10, 6, 4, 3]
stack:{}            heightArea[2, 6, 10, 6, 4, 3]
*/
int largestRectangleArea(int* heights, int heightsSize)
{
    int* stack = (int*)malloc(heightsSize * sizeof(int));
    memset(stack, 0, heightsSize * sizeof(int));
    int maxArea = 0, curArea;
    int stackIndex = 0;
    int i, sldx;
    int curHeightIndex;
    // 构造一个单调递增栈
    for (i = 0; i < heightsSize; i++) {
        while (stackIndex != 0 && heights[stack[stackIndex - 1]] > heights[i]) {
            curHeightIndex = stack[stackIndex - 1];
            stackIndex--;
            sldx = stackIndex == 0 ? -1 : stack[stackIndex - 1];
            curArea = heights[curHeightIndex] * (i - sldx - 1);
            maxArea = maxArea > curArea ? maxArea : curArea;
        }
        stack[stackIndex++] = i;
    }
    /*
    1, 2, 3, 4  curH = 3 stackIndex = 4,
    */
    while (stackIndex != 0) {
        curHeightIndex = stack[stackIndex - 1];
        stackIndex--;
        sldx = stackIndex == 0 ? -1 : stack[stackIndex - 1];
        curArea = heights[curHeightIndex] * (i - sldx - 1);
        maxArea = maxArea > curArea ? maxArea : curArea;
    }

    free(stack);
    return maxArea;
}

int largestRectangleArea(vector<int>& heights)
{
    int ret = 0;
    heights.push_back(0);
    vector<int> index;
    for (int i = 0; i < heights.size(); ++i) {
        while (index.size() > 0 && heights[index.back()] >= heights[i]) {
            int h = heights[index.back()];
            index.pop_back();
            int sidx = index.size() > 0 ? index.back() : -1;
            ret = max(ret, h * (i - sidx - 1));
        }
        index.push_back(i);
    }
    return ret;
}

TEST(MonStack, max_rect_area)
{
    int heights1[] = { 2, 1, 5, 6, 2, 3 };
    int height1 = 6;
    EXPECT_EQ(largestRectangleArea(heights1, height1), 10);
}

/*
{4, 2, 0, 3, 2, 5}
{0} {2, 0, 3, 2, 5} i = 1, idx = -1, h = 4, area = 4;
{1} {0, 3, 2, 5}  i = 2, idx = -1, h = 2, area = 4;
{2, 3} {2, 5}  i = 4, idx =
*/
TEST(MonStack, max_rect_area2)
{
    int heights1[] = { 4, 2, 0, 3, 2, 5 };
    int height1 = 6;
    EXPECT_EQ(largestRectangleArea(heights1, height1), 6);
}

/* 力扣第85题
给定一个仅包含 0 和 1 、大小为 rows x cols 的二维二进制矩阵，找出只包含 1 的最大矩形，并返回其面积
matrix = [["1","0","1","0","0"],["1","0","1","1","1"],["1","1","1","1","1"],["1","0","0","1","0"]
1 0 1 0 0
1 1 1 1 1
1 0 1 1 1
1 0 0 1 1

转化为上一题，第84题
*/
int maximalRectangle(char** matrix, int matrixSize, int* matrixColSize)
{
    int i, j;
    int col = 0;
    int retMax = 0, ret;
    for (i = 0; i < matrixSize; ++i) {
        col = col > matrixColSize[i] ? col : matrixColSize[i];
    }

    int* array = (int*)malloc(col * sizeof(int));
    memset(array, 0, sizeof(int) * col);
    for (i = 0; i < matrixSize; i++) {
        for (j = 0; j < matrixColSize[i]; ++j) {
            if (matrix[i][j] == '0') {
                array[j] = 0;
            } else {
                array[j] += 1;
            }
        }
        ret = largestRectangleArea(array, col);
        retMax = retMax > ret ? retMax : ret;
    }
    return retMax;
}

// 力扣第 739题
int* dailyTemperatures(int* temperatures, int temperaturesSize, int* returnSize)
{
    int* stack = (int*)malloc(temperaturesSize * sizeof(int));
    memset(stack, 0, temperaturesSize * sizeof(int));
    int* returnArray = (int*)malloc(temperaturesSize * sizeof(int));
    memset(returnArray, 0, temperaturesSize * sizeof(int));
    int stackIndex = -1;
    for (int i = 0; i < temperaturesSize; ++i) {
        while (stackIndex >= 0 && temperatures[stack[stackIndex]] < temperatures[i]) {
            returnArray[stack[stackIndex]] = i - stack[stackIndex];
            stackIndex--;
        }
        stack[++stackIndex] = i;
    }
    *returnSize = temperaturesSize;
    return returnArray;
}

// 力扣503题
int* nextGreaterElements(int* nums, int numsSize, int* returnSize)
{
    int size = (2 * numsSize - 1) * sizeof(int);
    int* stack = (int*)malloc(size);
    int stLen = -1;
    memset(stack, 0, size);
    int* retArray = (int*)malloc(numsSize * sizeof(int));
    int i = 0, index = 0;
    for (i = 0; i < numsSize; i++) {
        retArray[i] = -1;
    }

    for (i = 0; i < (2 * numsSize - 1); ++i) {
        index = i % numsSize;
        while (stLen >= 0 && nums[stack[stLen]] < nums[index]) {
            retArray[stack[stLen]] = nums[index];
            stLen--;
        }
        stack[++stLen] = index;
    }
    *returnSize = numsSize;
    free(stack);
    return retArray;
}

TEST(MonStack, GreaterElements)
{
    int array[] = { 1, 2, 1 };
    int arrayLen = 3;
    const int expOutput[3] = { 2, -1, 2 }; /*预计结果*/
    int returnSize = 0;
    int i;
    int* output = nextGreaterElements(array, arrayLen, &returnSize);

    EXPECT_EQ(returnSize, arrayLen);
    for (i = 0; i < arrayLen; ++i) {
        EXPECT_EQ(output[i], expOutput[i]);
    }
}
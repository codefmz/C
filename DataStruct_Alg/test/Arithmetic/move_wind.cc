
#include "errno.h"
#include "log.h"
#include "gtest/gtest.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <vector>

// 滑动窗口

int minSubArrayLen(int target, int* nums, int numsSize)
{
    int leftIdx = 0, rightIdx = 0;
    int sum = 0;
    int minLen = 0;
    while (rightIdx < numsSize) {
        if (sum < target) {
            sum += nums[rightIdx];
        } else {
            minLen = minLen < rightIdx - leftIdx + 1 ? minLen : rightIdx - leftIdx + 1;
            sum -= nums[leftIdx];
            leftIdx++;
        }
    }

    return minLen;
}

TEST(MOVEWIND, subArrayLen)
{
    int array[] = { 2, 3, 1, 2, 4, 3 };
    int len = sizeof(array) / sizeof(int);

    EXPECT_EQ(2, minSubArrayLen(7, array, len));
}

TEST(MOVEWIND, subArrayLen2)
{
    int array[] = { 1, 4, 4 };
    int len = sizeof(array) / sizeof(int);

    EXPECT_EQ(1, minSubArrayLen(4, array, len));
}

TEST(MOVEWIND, subArrayLen3)
{
    int array[] = { 1, 1, 1, 1, 1, 1, 1, 1 };
    int len = sizeof(array) / sizeof(int);

    EXPECT_EQ(0, minSubArrayLen(11, array, len));
}
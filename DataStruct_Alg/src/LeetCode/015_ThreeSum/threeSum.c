#include <stdlib.h>

int compare(const void* a, const void* b)
{
    return *(int*)a - *(int*)b;
}

void twoSum(int* nums, int left, int target, int right, int* returnSize, int** retrunColumnSize)
{
    int sum = 0;
    while (left < right) {
        sum = nums[left] + nums[right];
        if (sum < target) {
            ++left;
        } else if (sum > target) {
            --right;
        } else {
            retrunColumnSize[*returnSize][0] = -target;
            retrunColumnSize[*returnSize][1] = nums[left];
            retrunColumnSize[*returnSize][2] = nums[right];
            while (++left < right && nums[left] == nums[left - 1]) { };
            while (left < --right && nums[right] == nums[right + 1]) { };
            ++*returnSize;
        }
    }
}

int** threeSum(int* nums, int numsSize, int* returnSize, int** returnColumnSizes)
{
    qsort(nums, numsSize, sizeof(int), compare);
    *returnSize = 0;
    int i = 0;
    for (i = 0; i < numsSize; i++) {
        if (i == 0 || i > 0 && nums[i] == nums[i - 1]) {
            twoSum(nums, i + 1, numsSize - 1, -nums[i], returnSize, returnColumnSizes);
        }
    }
}
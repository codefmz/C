#include <math.h>
#include <stdlib.h>

int compareInt(const void* a, const void* b)
{
    return *(int*)a - *(int*)b;
}

int threeSumClosest(int* nums, int numsSize, int target)
{
    int min = INT_MAX;
    int i = 0, ret = 0;
    int sum = 0, l, r;

    qsort(nums, numsSize, sizeof(int), compareInt);
    for (; i < numsSize - 2; ++i) {
        if (i == 0 || i > 0 && nums[i] != nums[i - 1]) {
            l = i + 1;
            r = numsSize - 1;
            while (l < r) {
                sum = nums[i] + nums[l] + nums[r];
                if (sum < target) {
                    ++l;
                } else if (sum > target) {
                    --r;
                } else {
                    return sum;
                }
                if (min > abs(sum - target)) {
                    ret = sum;
                    min = abs(sum - target);
                }
            }
        }
    }
    return ret;
}
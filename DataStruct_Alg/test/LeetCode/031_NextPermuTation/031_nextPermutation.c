void swap(int* p1, int* p2)
{
    int temp = *p1;
    *p1 = *p2;
    *p2 = temp;
}

void reverseDownToUp(int* nums, int left, int right)
{
    while (left < right) {
        swap(nums + left, nums + right);
        ++left;
        --right;
    }
}

void nextPermutation(int* nums, int numSize)
{
    int i = numSize - 1;
    int k = 0;
    int temp = 0;

    for (; i > 0; --i) {
        if (nums[i - 1] < nums[i]) {
            break;
        }
    }

    if (i == 0) {
        reverseDownToUp(nums, 0, numSize - 1);
        return;
    }

    i--;
    for (k = numSize - 1; k > i; --k) {
        if (nums[k] > nums[i]) {
            break;
        }
    }

    swap(nums + i, nums + k);
    reverseDownToUp(nums, i + 1, numSize - 1);
    return;
}
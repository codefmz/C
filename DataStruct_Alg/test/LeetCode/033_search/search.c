int search(int* nums, int numsSize, int target)
{
    int left = 0, right = numsSize - 1;
    int mid = 0;
    while (left <= right) {
        mid = (left + right) / 2;
        if (nums[mid] == target) {
            return mid;
        }

        if (target < nums[mid]) {
            if (nums[mid] < nums[left]) {
                right = mid - 1;
                continue;
            }
            if (target < nums[left]) {
                left = mid + 1;
            } else {
                right = mid - 1;
            }
        }

        if (target > nums[mid]) {
            if (nums[mid] > nums[right]) {
                left = mid + 1;
                continue;
            }

            if (target > nums[right]) {
                right = mid - 1;
            } else {
                left = mid + 1;
            }
        }
    }
    return -1;
}
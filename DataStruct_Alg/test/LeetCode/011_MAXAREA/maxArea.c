int maxArea(int* height, int heightSize)
{
    int left = 0, right = heightSize - 1;
    int minHeight = height[left] < height[right] ? height[left] : height[right];
    int curArea = (right - left) * minHeight;
    int res = curArea;
    while (left < right) {
        if (height[left] < height[right]) {
            ++left;
        } else {
            --right;
        }
        minHeight = height[left] < height[right] ? height[left] : height[right];
        curArea = (right - left) * minHeight;
        res = curArea > res ? curArea : res;
    }
    return res;
}
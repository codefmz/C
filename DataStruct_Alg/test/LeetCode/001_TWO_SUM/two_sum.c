#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int val;
    int index;
} Object, *PObject;

int compare(const void* o1, const void* o2)
{
    return ((PObject)o1)->val - ((PObject)o2)->val;
}
int* twoSum(int* nums, int numsSize, int target, int* returnSize)
{
    PObject pObject = (PObject)malloc(sizeof(Object) * numsSize);
    for (size_t i = 0; i < numsSize; i++) {
        pObject[i].index = i;
        pObject[i].val = nums[i];
    }
    qsort(pObject, numsSize, sizeof(Object), compare);
    int* results = malloc(2 * sizeof(int));
    int left = 0, right = numsSize - 1;
    while (left < right) {
        int sum = pObject[left].val + pObject[right].val;
        if (sum < target) {
            ++left;
        } else if (sum > target) {
            --right;
        } else {
            results[0] = pObject[left].index;
            results[1] = pObject[right].index;
            *returnSize = 2;
            break;
        }
    }
    free(pObject);
    return results;
}

int g_cnt = 0;
void testTwoNum()
{
    // int nums[] = {-1, -2, -3, -4, -5};
    // int target = -8;
    // int nums[] = {0,4,3,0};
    // int target = 0;
    int nums[] = { 3, 2, 3 };
    int size = sizeof(nums) / sizeof(*nums);
    int target = 6;
    int count = 0;
    int hh = g_cnt;
    for (int i = 0; i < 19; ++i) {
        printf("i = %d", i);
    }

    int* indexes = twoSum(nums, size, target, &count);
    if (indexes != NULL) {
        printf("%d %d\n", indexes[0], indexes[1]);
    } else {
        printf("Not found\n");
    }
    free(indexes);
}

// 线程函数
void* thread_function(void* arg)
{
    int thread_id = *(int*)arg;
    printf("Thread ID: %d\n", thread_id);
    // 执行线程任务
    int hh = g_cnt;
    // 退出线程
    pthread_exit(NULL);
}

int main(int argc, char** argv)
{
    pthread_t thread_id;
    int thread_arg = 123; // 示例线程参数

    // 创建线程
    int ret = pthread_create(&thread_id, NULL, thread_function, (void*)&thread_arg);
    if (ret != 0) {
        printf("Error creating thread; return code from pthread_create() is %d\n", ret);
        exit(EXIT_FAILURE);
    }
    g_cnt = 100;
    int hh = g_cnt;
    testTwoNum();
    // 主线程等待新创建的线程结束
    ret = pthread_join(thread_id, NULL);
    if (ret != 0) {
        printf("Error joining thread; return code from pthread_join() is %d\n", ret);
        exit(EXIT_FAILURE);
    }

    printf("Thread joined\n");

    return 0;
}
#include "errno.h"
#include "log.h"
#include "gtest/gtest.h"
#include <stdio.h>
#include <stdlib.h>
#include <vector>

/* 6 */
typedef struct {
    int* buf;
    int size;
    int read;
    int write;
} MyCircularQueue;

MyCircularQueue* myCircularQueueCreate(int k)
{
    k++;
    MyCircularQueue* queue = (MyCircularQueue*)malloc(sizeof(MyCircularQueue));
    memset(queue, 0, sizeof(MyCircularQueue));
    queue->buf = (int*)malloc(k * sizeof(int));
    memset(queue->buf, 0, k * sizeof(int));
    queue->size = k;
    return queue;
}

bool myCircularQueueEnQueue(MyCircularQueue* obj, int value)
{
    int newWrite = (obj->write + 1) % obj->size;
    if (obj->read == newWrite) {
        return false;
    }

    (void)memcpy(&obj->buf[obj->write], &value, sizeof(int));
    obj->write = newWrite;
    return true;
}

bool myCircularQueueDeQueue(MyCircularQueue* obj)
{
    if (obj->read == obj->write) {
        return false;
    }

    obj->read = (obj->read + 1) % obj->size;
    return true;
}

int myCircularQueueFront(MyCircularQueue* obj)
{
    if (obj->read == obj->write) {
        return -1;
    }
    return obj->buf[obj->read];
}

int myCircularQueueRear(MyCircularQueue* obj)
{
    if (obj->read == obj->write) {
        return -1;
    }
    return obj->buf[(obj->write + obj->size - 1) % obj->size];
}

bool myCircularQueueIsEmpty(MyCircularQueue* obj)
{
    return obj->read == obj->write;
}

bool myCircularQueueIsFull(MyCircularQueue* obj)
{
    return obj->read == (obj->write + 1) % obj->size;
}

void myCircularQueueFree(MyCircularQueue* obj)
{
    free(obj->buf);
    free(obj);
}

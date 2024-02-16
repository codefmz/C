#ifndef _PRIORITY_QUEUE_H_
#define _PRIORITY_QUEUE_H_

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef USE_MY_PRIORITY_QUEUE
typedef int (*IntCompare)(int a, int b);
typedef struct myPriorityQueue {
    int size;
    int* array;
    int capacity;
    IntCompare comp;
} PriorityQueue;

PriorityQueue* CreatePriorityQueue(int capacity, IntCompare comp)
{
    if (capacity <= 0 || comp == NULL) {
        return NULL;
    }

    PriorityQueue* pq = (PriorityQueue*)malloc(sizeof(PriorityQueue));
    memset(pq, 0, sizeof(PriorityQueue));
    pq->array = (int*)malloc(sizeof(int) * capacity);
    memset(pq->array, 0, sizeof(int) * capacity);
    pq->capacity = capacity;
    pq->comp = comp;

    return pq;
}

static inline void intSwap(int* a, int* b)
{
    *a = *a ^ *b;
    *b = *a ^ *b;
    *a = *a ^ *b;
}

static void pqPushBuild(PriorityQueue* pq)
{
    int* array = pq->array;
    int size = pq->size;
    IntCompare comp = pq->comp;
    int i = size;

    while (i > 1) {
        if (comp(array[i], array[i / 2]) > 0) {
            intSwap(&array[i], &array[i / 2]);
            i = i / 2;
        } else {
            break;
        }
    }
}

int PQPush(PriorityQueue* pq, int elem)
{
    if (pq->size + 2 > pq->capacity) {
        return -1;
    }
    ++pq->size;
    pq->array[pq->size] = elem;
    pqPushBuild(pq);
}

void PQPop(PriorityQueue* pq)
{
    int* array = pq->array;
    int size;
    IntCompare comp = pq->comp;
    int i = 1, j;

    array[1] = array[pq->size];
    --pq->size;
    size = pq->size;

    while (1) {
        j = 2 * i;
        if (j + 1 <= size && comp(array[j + 1], array[j])) {
            j = j + 1;
        }
        if (comp(array[j], array[i])) {
            intSwap(&array[i], &array[j]);
            i = j;
        } else {
            break;
        }
    }
}

int Top(PriorityQueue* pq)
{
    if (pq->size == 0) {
        printf("Top error : pq is empty!");
        return -1;
    }
    return pq->array[1];
}

void FreePQ(PriorityQueue* pq)
{
    free(pq->array);
    pq = NULL;
}

#else
typedef struct myPQNode {
    int val;
    struct myPQNode* next;
} PQNode;

typedef struct {
    PQNode** nodes;
    int size;
} PriorityQueue;

static inline void swap(PQNode** a, PQNode** b)
{
    PQNode* tmp = *a;
    *a = *b;
    *b = tmp;
}

static inline int left(int i)
{
    return i * 2 + 1;
}

static inline int right(int i)
{
    return left(i) + 1;
}

static inline int parent(int i)
{
    return (i - 1) / 2;
}

void queue_dump(PriorityQueue* queue)
{
    int i;
    for (i = 0; i < queue->size; i++) {
        printf("%d ", queue->nodes[i]->val);
    }
    printf("\n");
}

static void percolate_up(PQNode** nodes, int i)
{
    while (i >= 0 && nodes[parent(i)]->val > nodes[i]->val) {
        swap(nodes + parent(i), nodes + i);
        i = parent(i);
    }
}

static void percolate_down(PQNode** nodes, int size)
{
    int i, min;
    for (i = 0; left(i) < size; i = min) {
        if (right(i) < size) {
            min = nodes[left(i)]->val < nodes[right(i)]->val ? left(i) : right(i);
        } else {
            min = left(i);
        }

        if (nodes[min]->val < nodes[i]->val) {
            swap(nodes + min, nodes + i);
        } else {
            break;
        }
    }
}

static void heap_build(PriorityQueue* queue)
{
    PQNode** nodes = queue->nodes;
    int i, size, j, min;

    size = queue->size;
    for (i = queue->size / 2 - 1; i > 0; i--) {
        for (j = i; j >= 0; j = min) {
            if (right(i) < size) {
                min = nodes[left(i)]->val < nodes[right(i)]->val ? left(i) : right(i);
            } else {
                min = left(i);
            }
            if (nodes[min]->val < nodes[i]->val) {
                swap(nodes + min, nodes + i);
            } else {
                break;
            }
        }
    }
}

void put(PriorityQueue* queue, PQNode* node)
{
    queue->nodes[queue->size++] = node;
    percolate_up(queue->nodes, queue->size - 1);
}

PQNode* get(PriorityQueue* queue)
{
    int i;
    PQNode* p = queue->nodes[0];
    swap(queue->nodes, queue->nodes + queue->size - 1);
    --queue->size;
    percolate_down(queue->nodes, queue->size);
    return p;
}

PriorityQueue* init(int size)
{
    PriorityQueue* queue = malloc(sizeof(PriorityQueue));
    queue->nodes = malloc(size * sizeof(PQNode));
    queue->size = 0;
    return queue;
}

void freePq(PriorityQueue* pq)
{
    free(pq->nodes);
    free(pq);
    pq = NULL;
}

#endif

#endif
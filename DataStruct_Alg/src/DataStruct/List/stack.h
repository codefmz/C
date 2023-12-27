#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct myStack {
    uintptr_t* data;
    uint32_t dataSize;
    uint32_t capacity;
    uint32_t topOfStack;
    uint32_t reserved;
} Stack;

void CreateStack(Stack* st, uint32_t maxElement, uint32_t dataSize)
{
    memset(st, 0, sizeof(Stack));
    st->data = (uintptr_t*)malloc(sizeof(uintptr_t) * maxElement);
    st->capacity = maxElement;
    st->dataSize = dataSize;
}

void MakeEmpty(Stack* st)
{
    while (st->topOfStack != 0) {
        free((void*)(st->data[st->topOfStack]));
        st->data[st->topOfStack] = 0;
        --st->topOfStack;
    }
}

void Push(const void* elem, Stack* st)
{
    if (st->topOfStack <= st->capacity) {
        void* newElem = malloc(st->dataSize);
        memcpy(newElem, elem, st->dataSize);
        st->data[++st->topOfStack] = (uintptr_t)newElem;
    } else {
        printf("size of stack is over capacity(%d)\r\n", st->capacity);
    }
}

void* Top(Stack* st)
{
    return (void*)st->data[st->topOfStack];
}

void Pop(void** elem, Stack* st)
{
    *elem = malloc(st->dataSize);
    memcpy(*elem, (void*)(st->data[st->topOfStack]), st->dataSize);
    free((void*)(st->data[st->topOfStack]));
    st->data[st->topOfStack] = 0;
    --st->topOfStack;
}

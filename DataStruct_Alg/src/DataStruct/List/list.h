#ifndef _LIST_H_
#define _LIST_H_

#include <stdint.h>
#include <stdlib.h>
#include <string.h>

typedef struct myListNode {
    struct myListNode* next;
    struct myListNode* pre;
    uintptr_t data;
    uint32_t dataSize;
    uint32_t reserved;
} ListNode;

typedef int (*Equal)(const void* a, const void* b);

typedef struct myList {
    ListNode head;
    ListNode* end;
    Equal equal;
    uint32_t size;
    uint32_t reserved;
} List;

void CreateList(List* list)
{
    memset(list, 0, sizeof(List));
}

void CreateListWithEqual(List* list, Equal equal)
{
    memset(list, 0, sizeof(List));
    list->equal = equal;
}

void MakeEmpty(List* list)
{
    ListNode* p = list->head.next;
    while (p != NULL) {
        ListNode* node = p->next;
        free((void*)(p->data));
        free(p);
        p = node;
    }
    list->size = 0;
    list->end = NULL;
}

int IsEmpty(List* list)
{
    return list->size == 0;
}

void PushBack(const void* data, uint32_t dataSize, List* list)
{
    ListNode* p = list->size == 0 ? &(list->head) : list->end;
    ListNode* node = (ListNode*)malloc(sizeof(ListNode));
    memset(node, 0, sizeof(ListNode));
    void* newData = malloc(dataSize);
    memset(newData, 0, dataSize);
    memcpy(newData, data, dataSize);
    node->data = (uintptr_t)newData;
    node->dataSize = dataSize;
    p->next = node;
    node->pre = p;
    list->end = node;
    ++list->size;
}

ListNode* Back(List* list)
{
    return list->end;
}

void RemoveBack(List* list, ListNode** pNode)
{
    ListNode* end = Back(list);
    ListNode* pre;
    if (end == NULL) {
        return;
    }
    pre = end->pre;
    pre->next = NULL;
    list->end = pre;
    *pNode = end;
    --list->size;
}

ListNode* Front(List* list)
{
    return list->head.next;
}

void PushFront(const void* data, uint32_t dataSize, List* list)
{
    ListNode* p = &(list->head);
    ListNode* front = p->next;
    ListNode* node = (ListNode*)malloc(sizeof(ListNode));
    memset(node, 0, sizeof(ListNode));
    void* newData = malloc(dataSize);
    memset(newData, 0, dataSize);
    memcpy(newData, data, dataSize);
    node->data = (uintptr_t)newData;
    p->next = node;
    node->next = front;
    node->pre = p;
    if (front != NULL) {
        front->pre = node;
    } else {
        list->end = node;
    }
    ++list->size;
}

void RemoveFront(List* list, ListNode** pNode)
{
    ListNode* front = Front(list);
    ListNode* frontNext;
    if (front == NULL) {
        return;
    }
    frontNext = front->next;
    list->head.next = frontNext;
    if (frontNext != NULL) {
        frontNext->pre = &(list->head);
    }
    list->end = frontNext;
    *pNode = front;
    --list->size;
}

void Reverse(List* list)
{
    ListNode* midNode;
    ListNode* head = &(list->head);
    ListNode* backNode = head->next;
    ListNode* temp;
    if (backNode == NULL) {
        return;
    }
    midNode = backNode->next;
    backNode->next = NULL;
    while (midNode != NULL) {
        backNode->pre = midNode;
        midNode->pre = head;
        head->next = midNode;
        temp = midNode->next;
        midNode->next = backNode;
        backNode = midNode;
        midNode = temp;
    }
}

typedef int (*TreverseFunc)(ListNode* node);

void Traverse(List* list, TreverseFunc func)
{
    ListNode* node = Front(list);
    while (node != NULL) {
        if (func(node) == 0) {
            return;
        }
        node = node->next;
    }
}

ListNode* FindList(const void* a, List* list)
{
    ListNode* node = Front(list);
    while (node != NULL) {
        if (list->equal(a, (void *)node->data) == 0) {
            return node;
        }
        node = node->next;
    }
}
#endif
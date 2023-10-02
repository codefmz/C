#ifndef _LIST_H_
#define _LIST_H_

#include "util.h"
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

typedef struct myListNode {
    uintptr_t data;
    uint32_t dataSize;
    uint32_t reserved;
    struct myListNode* next;
    struct myListNode* pre;
} ListNode;

typedef int (*Equal)(const void* a, const void* b);

typedef struct
{
    ListNode head; /* 空的头节点，占位用到 */
    ListNode* end; /* 最后一个节点，方面快速插入用到 */
    Equal equal;
    uint32_t size;
    uint32_t reseved;
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
        free((void*)p->data);
        free(p);
        p = node;
    }
    list->end = NULL;
    list->size = 0;
}

int IsEmpty(List* list)
{
    return list->size == 0;
}

ListNode* FindList(const void* data, List* list)
{
    ListNode* p = list->head.next;
    if (list->equal == NULL) {
        printf("please set euqal of list!");
        return NULL;
    } else {
        while (p) {
            if ((list->equal)((void*)p->data, data) == 0) {
                return p;
            }
            p = p->next;
        }
    }
    return NULL;
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
    node->pre = p;
    p->next = node;
    list->end = node;
    ++list->size;
}

void PushFront(const void* data, uint32_t dataSize, List* list)
{
    ListNode* p = &(list->head);
    ListNode* node = (ListNode*)malloc(sizeof(ListNode));
    memset(node, 0, sizeof(ListNode));
    void* newData = malloc(dataSize);
    memset(newData, 0, dataSize);
    memcpy(newData, data, dataSize);
    node->data = (uintptr_t)newData;
    node->dataSize = dataSize;
    node->pre = p;
    ListNode* front = p->next;
    node->next = front;
    if (front != NULL) {
        front->pre = node;
    }
    p->next = node;
    ++list->size;
}

ListNode* Front(List* list)
{
    return list->head.next;
}

ListNode* Back(List* list)
{
    return list->end;
}

void RemoveFront(List* list, ListNode** pNode)
{
    ListNode* p = Front(list);
    if (p == NULL) {
        return;
    }
    list->head.next = p->next;
    p->next->pre = &(list->head);
    *pNode = p;
    --list->size;
}

void RemoveBack(List* list, ListNode** pNode)
{
    ListNode* p = Back(list);
    if (p == NULL) {
        return;
    }
    ListNode* pre = p->pre;
    pre->next = NULL;
    list->end = pre;
    *pNode = p;
    --list->size;
}

void Reverse(List* list)
{
    ListNode* midNode;
    ListNode* temp;
    ListNode* head = &(list->head);
    ListNode* backNode = head->next;
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

#endif
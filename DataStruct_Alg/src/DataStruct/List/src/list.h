#ifndef _LIST_H_
#define _LIST_H_

#include "util.h"
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

typedef struct myNode {
    uintptr_t data;
    uint32_t dataSize;
    struct myNode* next;
    struct myNode* pre;
} Node;

typedef int (*Equal)(const void* a, const void* b);

typedef struct
{
    Node* head; /* 空的头节点，占位用到 */
    Node* end; /* 最后一个节点，方面快速插入用到 */
    Equal equal;
    uint32_t size;
    uint32_t reseved;
} List;

List* CreateList()
{
    List* list = (List*)malloc(sizeof(List));
    memset(list, 0, sizeof(List));
    list->head = (Node*)malloc(sizeof(Node));
    memset(list->head, 0, sizeof(Node));
    return list;
}

List* CreateListWithEqual(Equal equal)
{
    List* list = (List*)malloc(sizeof(List));
    memset(list, 0, sizeof(List));
    list->head = (Node*)malloc(sizeof(Node));
    list->equal = equal;
    memset(list->head, 0, sizeof(Node));
    return list;
}

void FreeList(List* list)
{
    Node* p = list->head;
    while (p != NULL) {
        Node* node = p->next;
        free((void*)p->data);
        free(p);
        p = node;
    }
    free(list);
}

int IsEmpty(List* list)
{
    return list->size == 0;
}

Node* Find(const void* data, List* list)
{
    Node* p = list->head->next;
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
    Node* p = list->size == 0 ? list->head : list->end;
    Node* node = (Node*)malloc(sizeof(Node));
    memset(node, 0, sizeof(Node));
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
    Node* p = list->head;
    Node* node = (Node*)malloc(sizeof(Node));
    memset(node, 0, sizeof(Node));
    void* newData = malloc(dataSize);
    memset(newData, 0, dataSize);
    memcpy(newData, data, dataSize);
    node->data = (uintptr_t)newData;
    node->dataSize = dataSize;
    node->pre = p;
    Node* front = p->next;
    node->next = front;
    if (front != NULL) {
        front->pre = node;
    }
    p->next = node;
    ++list->size;
}

Node* Front(List* list)
{
    return list->head->next;
}

Node* Back(List* list)
{
    return list->end;
}

void RemoveFront(List* list)
{
    Node* p = Front(list);
    if (p == NULL) {
        return;
    }
    list->head->next = p->next;
    p->next->pre = list->head;
    free((void*)p->data);
    free(p);
    --list->size;
}

void RemoveBack(List* list)
{
    Node* p = Back(list);
    if (p == NULL) {
        return;
    }
    Node* pre = p->pre;
    pre->next = NULL;
    list->end = pre;
    free((void*)p->data);
    free(p);
    --list->size;
}

void Reverse(List* list)
{
    Node* midNode;
    Node* temp;
    Node* head = list->head;
    Node* backNode = head->next;
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

typedef int (*TreverseFunc)(Node* node);
void Traverse(List* list, TreverseFunc func)
{
    Node* node = Front(list);
    while (node != NULL) {
        if (func(node) == 0) {
            return;
        }
        node = node->next;
    }
}
#endif
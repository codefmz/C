#include "list.h"
#include "util.h"
#include <stdio.h>
#include <string.h>

int EqualInt(const void* a, const void* b)
{
    return *(int*)a - *(int*)b;
}

void testInt()
{
    List* list = CreateListWithEqual(EqualInt);
    int temp = 1;
    PushBack(&temp, sizeof(temp), list);
    printf(" list size = %d\n", list->size);
    temp = 2;
    PushFront(&temp, sizeof(temp), list);
    temp = 3;
    PushBack(&temp, sizeof(temp), list);
    temp = 4;
    PushBack(&temp, sizeof(temp), list);
    temp = 5;
    PushBack(&temp, sizeof(temp), list);
    temp = 6;
    PushFront(&temp, sizeof(temp), list);
    printf(" list size = %d\n", list->size);
    Node* node = Front(list);
    printf(" list value: \t");
    while (node != NULL) {
        printf("%d --> ", *(int*)node->data);
        node = node->next;
    }
    printf("\n");
    FreeList(list);
}

int EqualStr(const void* a, const void* b)
{
    return strcmp((char*)a, (char*)b);
}

int traversePrint(Node* node)
{
    printf("%s --> ", (char*)node->data);
    return 1;
}

void testStr()
{
    List* list = CreateListWithEqual(EqualInt);
    const char* strTemp = "str1";
    PushBack(strTemp, strlen(strTemp) + 1, list);
    printf(" list size = %d\n", list->size);
    strTemp = "str2";
    PushFront(strTemp, strlen(strTemp) + 1, list);
    strTemp = "str3";
    PushBack(strTemp, strlen(strTemp) + 1, list);
    strTemp = "str4";
    PushBack(strTemp, strlen(strTemp) + 1, list);
    strTemp = "str5";
    PushBack(strTemp, strlen(strTemp) + 1, list);
    strTemp = "str6";
    PushFront(strTemp, strlen(strTemp) + 1, list);
    printf(" list size = %d\n", list->size);
    Node* node = Front(list);
    printf(" list value: \t");
    while (node != NULL) {
        printf("%s --> ", (char*)node->data);
        node = node->next;
    }
    printf("\n");

    Node* res = Find("str1", list);
    ASSERT_NOT_EQUAL(res, NULL);
    res = Find("str7", list);
    ASSERT_EQUAL(res, NULL);
    RemoveBack(list);
    ASSERT_EQUAL_STR((char*)(Back(list)->data), "str4");
    ASSERT_EQUAL(list->size, 5);
    RemoveFront(list);
    ASSERT_EQUAL_STR((char*)(Front(list)->data), "str2");
    ASSERT_EQUAL(list->size, 4);

    Reverse(list);
    node = Front(list);
    printf(" reverse list value: \t");
    while (node != NULL) {
        printf("%s --> ", (char*)node->data);
        node = node->next;
    }

    printf(" reverse list use traverse: \t");
    Traverse(list, traversePrint);
    printf("\n");
    FreeList(list);
}

int main(int argc, char** argv)
{
    testInt();
    testStr();
}
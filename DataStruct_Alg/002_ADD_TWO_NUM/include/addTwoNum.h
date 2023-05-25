#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct ListNode {
    int val;
    struct ListNode* next;
};

typedef struct ListNode ListNode;
struct ListNode* addTwoNumbers1(struct ListNode* l1, struct ListNode* l2);

//简化第一个版本，同时处理l1 与l2
struct ListNode* addTwoNumbers2(struct ListNode* l1, struct ListNode* l2);

struct ListNode* node_build(const char* digits);

void show(struct ListNode* ln);

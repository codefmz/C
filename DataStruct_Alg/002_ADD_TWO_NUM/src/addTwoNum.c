#include "addTwoNum.h"

struct ListNode* addTwoNumbers1(struct ListNode* l1, struct ListNode* l2)
{
    struct ListNode head, *tempNode = &head;
    bool step = false; //进位
    while ((l1 != NULL) && (l2 != NULL)) {
        int valSum = l1->val + l2->val;
        if (step) {
            ++valSum;
            step = false;
        }
        if (valSum > 9) {
            step = true;
            valSum -= 10;
        }
        struct ListNode* pNode = (ListNode*)malloc(sizeof(ListNode));
        memset(pNode, 0, sizeof(ListNode));
        pNode->val = valSum;
        tempNode->next = pNode;
        tempNode = pNode;
        l1 = l1->next;
        l2 = l2->next;
    }
    while (l1 != NULL) {
        if (step) {
            ++l1->val;
            step = false;
        }
        if (l1->val > 9) {
            step = true;
            l1->val -= 10;
        }
        tempNode->next = l1;
        tempNode = l1;
        l1 = l1->next;
    }
    while (l2 != NULL) {
        if (step) {
            ++l2->val;
            step = false;
        }
        if (l2->val > 9) {
            step = true;
            l2->val -= 10;
        }
        tempNode->next = l2;
        tempNode = l2;
        l2 = l2->next;
    }
    if (step) {
        struct ListNode* pNode = (ListNode*)malloc(sizeof(ListNode));
        memset(pNode, 0, sizeof(ListNode));
        pNode->val = 1;
        tempNode->next = pNode;
    }
    return head.next;
}

struct ListNode* addTwoNumbers2(struct ListNode* l1, struct ListNode* l2)
{
    ListNode *head = NULL, *tail;
    int sum = 0, step = 0;
    while (l1 != NULL || l2 != NULL) {
        sum = 0;
        if (l1 != NULL) {
            sum += l1->val;
            l1 = l1->next;
        }
        if (l2 != NULL) {
            sum += l2->val;
            l2 = l2->next;
        }
        sum += step;
        step = sum / 10;
        sum = sum % 10;
        if (head == NULL) {
            head = (ListNode*)malloc(sizeof(ListNode));
            memset(head, 0, sizeof(ListNode));
            head->val = sum;
            tail = head;
        } else {
            ListNode* pListNode = (ListNode*)malloc(sizeof(ListNode));
            pListNode->val = sum;
            pListNode->next = NULL;
            tail->next = pListNode;
            tail = tail->next;
        }
    }
    return head;
}

struct ListNode* node_build(const char* digits)
{
    struct ListNode *res, *p, *prev;
    int first = 1;
    int len = strlen(digits);
    const char* c = digits + len - 1;
    prev = NULL;
    while (len-- > 0) {
        p = malloc(sizeof(*p));
        if (first) {
            first = 0;
            res = p;
        }
        p->val = *c-- - '0';
        p->next = NULL;
        if (prev != NULL) {
            prev->next = p;
        }
        prev = p;
    }

    return res;
}

void show(struct ListNode* ln)
{
    int sum = 0, factor = 1;
    while (ln != NULL) {
        sum += ln->val * factor;
        factor *= 10;
        ln = ln->next;
    }
    printf("%d\n", sum);
}
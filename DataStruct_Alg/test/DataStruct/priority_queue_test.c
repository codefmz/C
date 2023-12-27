#include "config_my.h"
#include "priority_queue.h"
#include "util.h"

#ifdef USE_MY_PRIORITY_QUEUE
int compareLarge(int a, int b)
{
    return a - b > 0 ? 1 : 0;
}
void Test_Priority_Queue_001()
{
    int arrayInt[10] = { 5, 23, 23, 43, 1, 21, 12, 3234, 32, 1 };
    PriorityQueue* pq = CreatePriorityQueue(100, compareLarge);
    for (int i = 0; i < 10; i++) {
        PQPush(pq, arrayInt[i]);
    }

    ASSERT_EQUAL(Top(pq), 3234);
    PQPop(pq);
    ASSERT_EQUAL(Top(pq), 43);
    ASSERT_EQUAL(pq->size, 9);
    PQPop(pq);
    ASSERT_EQUAL(Top(pq), 32);
    PQPop(pq);
    ASSERT_EQUAL(Top(pq), 23);
    PQPop(pq);
    ASSERT_EQUAL(Top(pq), 23);
    PQPop(pq);
    ASSERT_EQUAL(Top(pq), 21);
    PQPush(pq, 100);
    ASSERT_EQUAL(pq->size, 6);
    ASSERT_EQUAL(Top(pq), 100);
    PQPop(pq);
    ASSERT_EQUAL(Top(pq), 21);

    FreePQ(pq);
}
#else

void Test_Priority_Queue_001()
{
    int arrayInt[10] = { 5, 23, 23, 43, 1, 21, 12, 3234, 32, 1 };
    PQNode pqNode[10] = { 0 };
    PriorityQueue* pq = init(10);
    for (int i = 0; i < 10; i++) {
        pqNode[i].val = arrayInt[i];
        pqNode[i].next = NULL;
        put(pq, pqNode + i);
    }
    ASSERT_EQUAL(get(pq)->val, 1);
    ASSERT_EQUAL(get(pq)->val, 1);
    ASSERT_EQUAL(pq->size, 8);
    ASSERT_EQUAL(get(pq)->val, 5);
    ASSERT_EQUAL(get(pq)->val, 12);
    PQNode pqNode1 = { .val = 10, .next = NULL };
    put(pq, &pqNode1);
    ASSERT_EQUAL(get(pq)->val, 10);
    ASSERT_EQUAL(get(pq)->val, 21);
    ASSERT_EQUAL(get(pq)->val, 23);
    freePq(pq);
}

struct ListNode {
    int val;
    struct ListNode* next;
};

struct ListNode* mergeKLists(struct ListNode** lists, int listsSize)
{
    if (listsSize == 0) {
        return NULL;
    }

    if (listsSize == 1) {
        return lists[0];
    }

    int i;
    struct ListNode dummy;
    struct ListNode* prev;

    PriorityQueue* pq = init(listsSize);
    dummy.next = NULL;
    prev = &dummy;

    for (i = 0; i < listsSize; i++) {
        if (lists[i] != NULL) {
            put(pq, (struct ListNode*)(lists[i]));
        }
    }
    heap_build(pq);
    while (pq->size > 0) {
        struct ListNode* n = get(pq);
        prev->next = n;
        ;
        prev = n;
        if (n->next != NULL) {
            put(pq, n->next);
        }
        n->next = NULL;
    }
    return dummy.next;
}

void Test_Priority_Queue_002()
{
}

#endif

int main(int argc, char** argv)
{
    Test_Priority_Queue_001();
}

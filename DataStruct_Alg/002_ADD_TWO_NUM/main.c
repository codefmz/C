#include "addTwoNum.h"
int main(int argc, char** argv)
{
    if (argc < 3) {
        fprintf(stderr, "Usage: ./test n1 n2\n");
        exit(-1);
    }
    struct ListNode* l1 = node_build(argv[1]);
    struct ListNode* l2 = node_build(argv[2]);
    struct ListNode* res = addTwoNumbers2(l1, l2);
    show(l1);
    show(l2);
    show(res);
    return 0;
}
#include "radixTree.h"
#include "gtest/gtest.h"
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#define MASK 0xFFFFFFFF

// {
//     void* tree;
//     int a = 1, b = 2, c = 3, d = 0;
//     uintptr_t ptr = 0;
//     int ret;

//     tree = util_radix_tree_create(0);
//     ret = util_radix32tree_insert(tree, 1, MASK, (uintptr_t)&a);
//     ret = util_radix32tree_insert(tree, 2, MASK, (uintptr_t)&b);
//     ret = util_radix32tree_insert(tree, 3, MASK, (uintptr_t)&c);

//     ptr = util_radix32tree_find(tree, 1);
//     printf("**************a:%p, b:%p, c:%p, ptr:%p-%p\n", &a, &b, &c, &ptr, ptr);
//     ptr = util_radix32tree_find(tree, 2);
//     printf("**************a:%p, b:%p, c:%p, ptr:%p-%p\n", &a, &b, &c, &ptr, ptr);
//     ptr = util_radix32tree_find(tree, 3);
//     printf("**************a:%p, b:%p, c:%p, ptr:%p-%p\n", &a, &b, &c, &ptr, ptr);
//     util_radix32tree_delete(tree, 3, MASK);
//     ptr = util_radix32tree_find(tree, 3);
//     ret = ptr;
//     if (ret == -1) {
//         printf("not find\n");
//     } else {
//         d = *(int*)ptr;
//     }
//     printf("**************a:%p, b:%p, c:%p, d:%d, ptr:%p-%p\n", &a, &b, &c, d, &ptr, ptr);
//     util_radix_tree_destroy(tree);

//     return 0;
// }
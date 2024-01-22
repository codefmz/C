#include <radixTree.h>
#include <stdio.h>
#include <stdlib.h>

#define UTIL_RADIX_NO_VALUE (uintptr_t)(-1)

typedef struct util_radix_node_s util_radix_node_t;

struct util_radix_node_s {
    util_radix_node_t* right;
    util_radix_node_t* left;
    util_radix_node_t* parent;
    uintptr_t value;
};

typedef struct {
    util_radix_node_t* root;
    util_radix_node_t* free;
} util_radix_tree_t;

int util_radix32tree_insert(void* vtree, uint32_t key, uint32_t mask, uintptr_t value);

static util_radix_node_t* util_radix_alloc(util_radix_tree_t* tree)
{
    util_radix_node_t* p;

    if (tree->free) {
        p = tree->free;
        tree->free = tree->free->right;
        return p;
    }
    p = malloc(sizeof(util_radix_node_t));
    if (p == NULL) {
        return NULL;
    }

    return p;
}

static void util_radix_free(util_radix_node_t* node)
{
    if (node == NULL) {
        return;
    }
    free(node);
}

void* util_radix_tree_create(int preallocate)
{
    uint32_t key, mask, inc;
    util_radix_tree_t* tree;

    tree = malloc(sizeof(util_radix_tree_t));
    if (tree == NULL) {
        return NULL;
    }

    tree->free = NULL;

    tree->root = util_radix_alloc(tree);
    if (tree->root == NULL) {
        return NULL;
    }

    tree->root->right = NULL;
    tree->root->left = NULL;
    tree->root->parent = NULL;
    tree->root->value = UTIL_RADIX_NO_VALUE;

    if (preallocate <= 0) {
        return tree;
    }

    mask = 0;
    inc = 0x80000000;

    while (preallocate--) {

        key = 0;
        mask >>= 1;
        mask |= 0x80000000;

        do {
            if (util_radix32tree_insert(tree, key, mask, UTIL_RADIX_NO_VALUE) != 0) {
                return NULL;
            }

            key += inc;

        } while (key);

        inc >>= 1;
    }

    return tree;
}

static util_radix_node_t* radix_tree_postorder(util_radix_node_t* node)
{
    util_radix_node_t* p;

    if (NULL != node->left) {
        p = radix_tree_postorder(node->left);
        if (NULL != p) {
            return p;
        }
    }
    if (NULL != node->right) {
        p = radix_tree_postorder(node->right);
        if (NULL != p) {
            return p;
        }
    }
    util_radix_free(node);

    return NULL;
}

void util_radix_tree_destroy(void* vtree)
{
    util_radix_tree_t* tree = (util_radix_tree_t*)vtree;
    util_radix_node_t* p;

    radix_tree_postorder(tree->root);
    while (tree->free) {
        p = tree->free;
        tree->free = tree->free->right;
        util_radix_free(p);
    }
}

int util_radix32tree_insert(void* vtree, uint32_t key, uint32_t mask,
    uintptr_t value)
{
    util_radix_tree_t* tree = (util_radix_tree_t*)vtree;
    uint32_t bit;
    util_radix_node_t *node, *next;

    bit = 0x80000000;

    node = tree->root;
    next = tree->root;

    while (bit & mask) {
        if (key & bit) {
            next = node->right;
        } else {
            next = node->left;
        }

        if (next == NULL) {
            break;
        }

        bit >>= 1;
        node = next;
    }

    if (next) {
        if (node->value != UTIL_RADIX_NO_VALUE) {
            return -3;
        }

        node->value = value;
        return 0;
    }

    while (bit & mask) {
        next = util_radix_alloc(tree);
        if (next == NULL) {
            return -1;
        }

        next->right = NULL;
        next->left = NULL;
        next->parent = node;
        next->value = UTIL_RADIX_NO_VALUE;

        if (key & bit) {
            node->right = next;

        } else {
            node->left = next;
        }

        bit >>= 1;
        node = next;
    }

    node->value = value;

    return 0;
}

int util_radix32tree_delete(void* vtree, uint32_t key, uint32_t mask)
{
    util_radix_tree_t* tree = (util_radix_tree_t*)vtree;
    uint32_t bit;
    util_radix_node_t* node;

    bit = 0x80000000;
    node = tree->root;

    while (node && (bit & mask)) {
        if (key & bit) {
            node = node->right;

        } else {
            node = node->left;
        }

        bit >>= 1;
    }

    if (node == NULL) {
        return -1;
    }

    if (node->right || node->left) {
        if (node->value != UTIL_RADIX_NO_VALUE) {
            node->value = UTIL_RADIX_NO_VALUE;
            return 0;
        }

        return -3;
    }

    for (;;) {
        if (node->parent->right == node) {
            node->parent->right = NULL;

        } else {
            node->parent->left = NULL;
        }

        node->right = tree->free;
        tree->free = node;

        node = node->parent;

        if (node->right || node->left) {
            break;
        }

        if (node->value != UTIL_RADIX_NO_VALUE) {
            break;
        }

        if (node->parent == NULL) {
            break;
        }
    }

    return 0;
}

uintptr_t util_radix32tree_find(void* vtree, uint32_t key)
{
    util_radix_tree_t* tree = (util_radix_tree_t*)vtree;
    uint32_t bit;
    uintptr_t value;
    util_radix_node_t* node;

    bit = 0x80000000;
    value = UTIL_RADIX_NO_VALUE;
    node = tree->root;

    while (node) {
        if (node->value != UTIL_RADIX_NO_VALUE) {
            value = node->value;
        }

        if (key & bit) {
            node = node->right;

        } else {
            node = node->left;
        }

        bit >>= 1;
    }

    return value;
}

int util_radix64tree_insert(void* vtree, uint64_t key, uint64_t mask,
    uintptr_t value)
{
    util_radix_tree_t* tree = (util_radix_tree_t*)vtree;
    uint64_t bit;
    util_radix_node_t *node, *next;

    bit = 0x8000000000000000;

    node = tree->root;
    next = tree->root;

    while (bit & mask) {
        if (key & bit) {
            next = node->right;

        } else {
            next = node->left;
        }

        if (next == NULL) {
            break;
        }

        bit >>= 1;
        node = next;
    }

    if (next) {
        if (node->value != UTIL_RADIX_NO_VALUE) {
            return -3;
        }

        node->value = value;
        return 0;
    }

    while (bit & mask) {
        next = util_radix_alloc(tree);
        if (next == NULL) {
            return -1;
        }

        next->right = NULL;
        next->left = NULL;
        next->parent = node;
        next->value = UTIL_RADIX_NO_VALUE;

        if (key & bit) {
            node->right = next;

        } else {
            node->left = next;
        }

        bit >>= 1;
        node = next;
    }

    node->value = value;

    return 0;
}

int util_radix64tree_delete(void* vtree, uint64_t key, uint64_t mask)
{
    util_radix_tree_t* tree = (util_radix_tree_t*)vtree;
    uint64_t bit;
    util_radix_node_t* node;

    bit = 0x8000000000000000;
    node = tree->root;

    while (node && (bit & mask)) {
        if (key & bit) {
            node = node->right;

        } else {
            node = node->left;
        }

        bit >>= 1;
    }

    if (node == NULL) {
        return -1;
    }

    if (node->right || node->left) {
        if (node->value != UTIL_RADIX_NO_VALUE) {
            node->value = UTIL_RADIX_NO_VALUE;
            return 0;
        }

        return -1;
    }

    for (;;) {
        if (node->parent->right == node) {
            node->parent->right = NULL;

        } else {
            node->parent->left = NULL;
        }

        node->right = tree->free;
        tree->free = node;

        node = node->parent;

        if (node->right || node->left) {
            break;
        }

        if (node->value != UTIL_RADIX_NO_VALUE) {
            break;
        }

        if (node->parent == NULL) {
            break;
        }
    }

    return 0;
}

uintptr_t util_radix64tree_find(void* vtree, uint64_t key)
{
    util_radix_tree_t* tree = (util_radix_tree_t*)vtree;
    uint64_t bit;
    uintptr_t value;
    util_radix_node_t* node;

    bit = 0x8000000000000000;
    value = UTIL_RADIX_NO_VALUE;
    node = tree->root;

    while (node) {
        if (node->value != UTIL_RADIX_NO_VALUE) {
            value = node->value;
        }

        if (key & bit) {
            node = node->right;

        } else {
            node = node->left;
        }

        bit >>= 1;
    }

    return value;
}

int util_radix128tree_insert(void* vtree, uint8_t* key, uint8_t* mask,
    uintptr_t value)
{
    util_radix_tree_t* tree = (util_radix_tree_t*)vtree;
    uint8_t bit;
    uint32_t i;
    util_radix_node_t *node, *next;

    i = 0;
    bit = 0x80;

    node = tree->root;
    next = tree->root;

    while (bit & mask[i]) {
        if (key[i] & bit) {
            next = node->right;

        } else {
            next = node->left;
        }

        if (next == NULL) {
            break;
        }

        bit >>= 1;
        node = next;

        if (bit == 0) {
            if (++i == 16) {
                break;
            }

            bit = 0x80;
        }
    }

    if (next) {
        if (node->value != UTIL_RADIX_NO_VALUE) {
            return -3;
        }

        node->value = value;
        return 0;
    }

    while (bit & mask[i]) {
        next = util_radix_alloc(tree);
        if (next == NULL) {
            return -1;
        }

        next->right = NULL;
        next->left = NULL;
        next->parent = node;
        next->value = UTIL_RADIX_NO_VALUE;

        if (key[i] & bit) {
            node->right = next;

        } else {
            node->left = next;
        }

        bit >>= 1;
        node = next;

        if (bit == 0) {
            if (++i == 16) {
                break;
            }

            bit = 0x80;
        }
    }

    node->value = value;

    return 0;
}

int util_radix128tree_delete(void* vtree, uint8_t* key, uint8_t* mask)
{
    util_radix_tree_t* tree = (util_radix_tree_t*)vtree;
    uint8_t bit;
    uint32_t i;
    util_radix_node_t* node;

    i = 0;
    bit = 0x80;
    node = tree->root;

    while (node && (bit & mask[i])) {
        if (key[i] & bit) {
            node = node->right;

        } else {
            node = node->left;
        }

        bit >>= 1;

        if (bit == 0) {
            if (++i == 16) {
                break;
            }

            bit = 0x80;
        }
    }

    if (node == NULL) {
        return -1;
    }

    if (node->right || node->left) {
        if (node->value != UTIL_RADIX_NO_VALUE) {
            node->value = UTIL_RADIX_NO_VALUE;
            return 0;
        }

        return -1;
    }

    for (;;) {
        if (node->parent->right == node) {
            node->parent->right = NULL;

        } else {
            node->parent->left = NULL;
        }

        node->right = tree->free;
        tree->free = node;

        node = node->parent;

        if (node->right || node->left) {
            break;
        }

        if (node->value != UTIL_RADIX_NO_VALUE) {
            break;
        }

        if (node->parent == NULL) {
            break;
        }
    }

    return 0;
}

uintptr_t util_radix128tree_find(void* vtree, uint8_t* key)
{
    util_radix_tree_t* tree = (util_radix_tree_t*)vtree;
    uint8_t bit;
    uintptr_t value;
    uint32_t i;
    util_radix_node_t* node;

    i = 0;
    bit = 0x80;
    value = UTIL_RADIX_NO_VALUE;
    node = tree->root;

    while (node) {
        if (node->value != UTIL_RADIX_NO_VALUE) {
            value = node->value;
        }

        if (key[i] & bit) {
            node = node->right;

        } else {
            node = node->left;
        }

        bit >>= 1;

        if (bit == 0) {
            i++;
            bit = 0x80;
        }
    }

    return value;
}
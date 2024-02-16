#ifndef SEARCH_QUEUE_H
#define SEARCH_QUEUE_H

#include <stdint.h>

typedef struct binaryNode {
    uint32_t value;
    struct binaryNode* left;
    struct binaryNode* right;
} BinaryNode;

typedef struct {
    BinaryNode* root;
    uint32_t size;
} BinaryTree;

BinaryTree* BinaryTreeCreate();

uint32_t BinaryTreeInsert(BinaryTree* tree, uint32_t value);

uint32_t BinaryTreeFind(BinaryTree* tree, uint32_t value);

uint32_t BinaryTreeErase(BinaryTree* tree, uint32_t value);

uint32_t BinaryTreeDelete(BinaryTree* tree);

typedef uint32_t (*TraverseFunc)(uint32_t value);

uint32_t BinaryTreeTraverse(BinaryTree* tree, TraverseFunc func);

#endif
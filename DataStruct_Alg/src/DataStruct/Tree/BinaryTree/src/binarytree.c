#include "binarytree.h"
#include "base.h"
#include "log.h"
#include <stdlib.h>
#include <string.h>

BinaryTree* BinaryTreeCreate()
{
    BinaryTree* tree = (BinaryTree*)malloc(sizeof(BinaryTree));
    memset(tree, 0, sizeof(BinaryTree));
    return tree;
}

static void BinaryTreeInsertHelp(BinaryNode** cur, uint32_t value)
{
    BinaryNode* node;
    if (*cur == NULL) {
        node = (BinaryNode*)malloc(sizeof(BinaryNode));
        memset(node, 0, sizeof(BinaryNode));
        node->value = value;
        *cur = node;
    } else {
        if ((*cur)->value <= value) {
            cur = &((*cur)->left);
        } else {
            cur = &((*cur)->right);
        }
    }
}

uint32_t BinaryTreeInsert(BinaryTree* tree, uint32_t value)
{
    BinaryTreeInsertHelp(&tree->root, value);
    return OK;
}

uint32_t BinaryTreeFind(BinaryTree* tree, uint32_t value)
{
    uint32_t size, row, index, i;

    BinaryNode** nodeArr = (BinaryNode**)malloc(tree->size / 2 * sizeof(BinaryNode*));
    BinaryNode** nodeArrTmp = (BinaryNode**)malloc(tree->size / 2 * sizeof(BinaryNode*));
    nodeArr[0] = tree->root;
    size = 1;

    while (size != 0) {
        row = size;
        index = 0;
        for (i = 0; i < row; ++i) {
            if (nodeArr[i]->value == value) {
                free(nodeArr);
                free(nodeArrTmp);
                return OK;
            }

            if (nodeArr[i]->left != NULL) {
                nodeArrTmp[index++] = nodeArr[i]->left;
            }

            if (nodeArr[i]->right != NULL) {
                nodeArrTmp[index++] = nodeArr[i]->right;
            }
        }

        memcpy((void*)nodeArr, (void*)nodeArrTmp, index * sizeof(BinaryNode*));
        size = index;
    }

    free(nodeArr);
    free(nodeArrTmp);
    return ERROR;
}

uint32_t BinaryTreeErase(BinaryTree* tree, uint32_t value)
{
    BinaryNode** cur = &(tree->root);

    while (*cur != NULL) {
        if ((*cur)->value < value) {
            cur = &((*cur)->left);
        } else if ((*cur)->value > value) {
            cur = &((*cur)->right);
        } else {
            if ((*cur)->left == NULL && (*cur)->right == NULL) {
                *cur = NULL;
                return OK;
            } else if ((*cur)->left != NULL && (*cur)->right == NULL) {
                *cur = (*cur)->left;
                return OK;
            } else if ((*cur)->left == NULL && (*cur)->right != NULL) {
                *cur = (*cur)->right;
                return OK;
            } else {
                (*cur)->value = (*cur)->right->value;
                value = (*cur)->right->value;
                *cur = (*cur)->right;
            }
        }
    }

    return ERROR;
}

uint32_t BinaryTreeDelete(BinaryTree* tree)
{
    uint32_t size, row, index, i;

    BinaryNode** nodeArr = (BinaryNode**)malloc(tree->size / 2 * sizeof(BinaryNode*));
    BinaryNode** nodeArrTmp = (BinaryNode**)malloc(tree->size / 2 * sizeof(BinaryNode*));
    nodeArr[0] = tree->root;
    size = 1;

    while (size != 0) {
        row = size;
        index = 0;
        for (i = 0; i < row; ++i) {
            if (nodeArr[i]->left != NULL) {
                nodeArrTmp[index++] = nodeArr[i]->left;
            }

            if (nodeArr[i]->right != NULL) {
                nodeArrTmp[index++] = nodeArr[i]->right;
            }

            free(nodeArr[i]);
        }

        memcpy((void*)nodeArr, (void*)nodeArrTmp, index * sizeof(BinaryNode*));
        size = index;
    }

    free(nodeArr);
    free(nodeArrTmp);
    free(tree);
    return OK;
}

uint32_t BinaryTreeTraverse(BinaryTree* tree, TraverseFunc func)
{
    uint32_t size, row, index, i;
    BinaryNode** nodeArr = (BinaryNode**)malloc(tree->size / 2 * sizeof(BinaryNode*));
    BinaryNode** nodeArrTmp = (BinaryNode**)malloc(tree->size / 2 * sizeof(BinaryNode*));
    nodeArr[0] = tree->root;
    size = 1;

    while (size != 0) {
        row = size;
        index = 0;
        for (i = 0; i < row; ++i) {
            if (nodeArr[i]->left != NULL) {
                nodeArrTmp[index++] = nodeArr[i]->left;
            }

            if (nodeArr[i]->right != NULL) {
                nodeArrTmp[index++] = nodeArr[i]->right;
            }

            func(nodeArr[i]->value);
        }
        memcpy((void*)nodeArr, (void*)nodeArrTmp, index * sizeof(BinaryNode*));
        size = index;
    }

    free(nodeArr);
    free(nodeArrTmp);
    return OK;
}
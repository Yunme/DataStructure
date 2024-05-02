//
// Created by zzqni on 2024/4/28.
//

#ifndef ANDROIDFRAMEWORKTEST_AVLSEARCH_H
#define ANDROIDFRAMEWORKTEST_AVLSEARCH_H

#include "Search.h"

typedef struct AVLNode {
    ElementType data;
    AVLNode *lc, *rc;
    int height;
} AVLNode, *AVLTree;

void AVL_InorderTraversal(const AVLTree &tree);

int AVL_getBalanceFactor(AVLNode *node);

void AVL_InsertNodeRecursive(AVLTree &node, const ElementType &data);

void AVL_InsertNode(AVLTree &tree, const ElementType &data);

void AVL_DeleteNodeRecursive(AVLTree &tree, const KeyType &key);

void AVL_DeleteNode(AVLTree &tree, const KeyType &key);

AVLNode *AVL_Search(AVLTree &tree, KeyType key, int *searchCount = nullptr);

void generateAVLImage(const AVLTree &tree);

#endif //ANDROIDFRAMEWORKTEST_AVLSEARCH_H

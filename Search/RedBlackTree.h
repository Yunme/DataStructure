//
// Created by zzqni on 2024/4/29.
//

#ifndef ANDROIDFRAMEWORKTEST_REDBLACKTREE_H
#define ANDROIDFRAMEWORKTEST_REDBLACKTREE_H

#include "Search.h"

#define BLACK 0
#define RED 1

typedef int ColorType;

typedef struct RBNode {
    ElementType data;

    ColorType color;
    RBNode *lc, *rc, *parent;
} RBNode, *RedBlackTree;

void RedBlack_Traversal(const RedBlackTree &tree);

RBNode *RedBlack_NewNode(RBNode *parent, const ElementType &element);

void RedBlack_rotateLeft(RedBlackTree &tree, RBNode *node);

void RedBlack_rotateRight(RedBlackTree &tree, RBNode *node);

void RedBlack_InsertFixUp(RedBlackTree &tree, RBNode *node);

void RedBlack_InsertNode(RedBlackTree &tree, const ElementType &element);

void RedBlack_DeleteNode(RedBlackTree &tree, const KeyType &key);

RBNode *RedBlack_Search(const RedBlackTree &tree, KeyType key, int &searchCount);

void generateRedBlackTreeImage(const RedBlackTree &tree);

#endif //ANDROIDFRAMEWORKTEST_REDBLACKTREE_H

//
// Created by zzqni on 2024/4/27.
//

#ifndef ANDROIDFRAMEWORKTEST_BITREESEARCH_H
#define ANDROIDFRAMEWORKTEST_BITREESEARCH_H

#include "Search.h"
#include "../Tree/BiTree.h"
#include "SqSearch.h"

typedef struct BSTNode {
    ElementType data;
    BSTNode *lc, *rc;
} BSTNode, *BSTree;

void BST_TraversalInOrder(const BSTree &tree, vector<BSTNode *> *nodeOrder = nullptr);

void BST_InsertRecursive(BSTree &tree, const ElementType &data);

void BST_Insert(BSTree &tree, const ElementType &data);

BSTNode *BST_SearchRecursive(const BSTree &tree, KeyType key);

BSTNode *BST_Search(BSTree &tree, KeyType key, int *searchCount = nullptr);

Status BST_Delete(BSTree &tree, KeyType key);

int BST_getLevel(BSTree &tree, KeyType key);

int BST_getLevelRecursive(BSTree &tree, KeyType key, int level = 0);

void generateBSTImage(const BSTree &tree);

#endif //ANDROIDFRAMEWORKTEST_BITREESEARCH_H

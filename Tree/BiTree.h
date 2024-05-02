//
// Created by zzqni on 2024/4/21.
//

#ifndef ANDROIDFRAMEWORKTEST_BITREE_H
#define ANDROIDFRAMEWORKTEST_BITREE_H

#include "../common.h"
#include "../StackQueue/SqStack.h"
#include <iostream>

using namespace std;

typedef struct BiNode {
    ElemType data;
    struct BiNode *lc, *rc;
} BiNode, *BiTree;


void BiTree_Init(BiTree &tree);

void BiTree_Cin_Create(BiTree &tree);

void BiTree_Create(BiTree &tree, const char *&array);

void BiTree_Traversal_DLR(BiTree tree);

void BiTree_Traversal_LDR(BiTree tree);

void BiTree_Traversal_LRD(BiTree tree);

void BiTree_Traversal_Stack(BiTree tree);

void BiTree_Traversal_Level(BiTree tree);

int BiTree_GetDepth(BiTree tree);

int BiTree_GetCount(BiTree tree);

int BiTree_GetLeafCount(BiTree tree);

void BiTree_FindNode(BiTree tree, ElemType e, BiNode *&node);

void BiTree_Assign(BiTree tree, BiNode *&node, ElemType e);

void BiTree_GetParent(BiTree tree, BiNode *search, BiTree &parent);

void BiTree_GetLeftChild(BiTree tree, BiNode *search, BiTree &leftChild);

void BiTree_GetRightChild(BiTree tree, BiNode *search, BiTree &rightChild);

void BiTree_GetLeftSibling(BiTree tree, BiNode *search, BiTree &leftSibling);

void BiTree_GetRightSibling(BiTree tree, BiNode *search, BiTree &rightSibling);

void BiTree_InsertChild(BiTree &tree, ElemType search, int LR, ElemType e);

void BiTree_DeleteChild(BiTree &tree, ElemType search, int LR);


#endif //ANDROIDFRAMEWORKTEST_BITREE_H

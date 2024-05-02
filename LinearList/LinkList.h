//
// Created by zzqni on 2024/4/16.
//

#ifndef ANDROIDFRAMEWORKTEST_LINKLIST_H
#define ANDROIDFRAMEWORKTEST_LINKLIST_H

#include "../common.h"

using namespace std;

typedef struct LinkNode {
    ElemType data;
    struct LinkNode *next;
} LinkNode, *LinkList;

Status InitList_L(LinkList &L);

int ListEmpty_L(LinkList L);

Status DestroyList_L(LinkList &L);

int ClearList_L(LinkList &L);

int GetLength_L(LinkList L);

int GetElem_L(LinkList L, int i, ElemType &e);

LinkNode *LocateElem_L(LinkList L, ElemType e);

Status GetElem_L(LinkList L, int index, LinkNode &node);

int LocateElemIndex_L(LinkList L, ElemType e);

int InsertNode_L(LinkList &L, int index, ElemType e);

int DeleteNode_L(LinkList &L, int index, ElemType &e);

void CreateList_H(LinkList &L, int n);

void CreateList_T(LinkList &L, int n);

void CreateList_Array(LinkList &L, ElemType *array);

void LinkList_Print(LinkList L);

#endif //ANDROIDFRAMEWORKTEST_LINKLIST_H

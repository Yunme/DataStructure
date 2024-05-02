//
// Created by zzqni on 2024/4/17.
//

#ifndef ANDROIDFRAMEWORKTEST_DULINKLIST_H
#define ANDROIDFRAMEWORKTEST_DULINKLIST_H

#include "../common.h"
#include <iostream>

using namespace std;

typedef struct DuLNode {
    ElemType data;
    struct DuLNode *prior, *next;
} DuLNode, *DuLinkList;

DuLNode *GetElemP_DuL(DuLinkList &L, int i);

Status ListInsert_Dul(DuLinkList &L, int i, ElemType e);

Status ListDelete_Dul(DuLinkList &L, int i, ElemType &e);

void CreateDuLinkList_Array(DuLinkList &L, ElemType *array);

void DuLinkList_Print(DuLinkList L);

#endif //ANDROIDFRAMEWORKTEST_DULINKLIST_H

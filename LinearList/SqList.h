//
// Created by zzqni on 2024/4/16.
//

#ifndef ANDROIDFRAMEWORKTEST_SQLIST_H
#define ANDROIDFRAMEWORKTEST_SQLIST_H


#include "../common.h"

typedef struct {
    ElemType *elem;
    int length;
} SqList;

int InitList_Sq(SqList &L);

void DestroyList(SqList &L);

void ClearList(SqList &L);

int GetLength(SqList L);

int isEmpty(SqList L);

int GetElem(SqList L, int i, ElemType &e);

int LocateElem(SqList L, ElemType e);

Status ListInsert_Sq(SqList &L, int i, ElemType e);

Status ListDelete_Sq(SqList &L, int i);

void ListSq_Print(SqList L);

void ListSq_Create(SqList &L, ElemType *array);


#endif //ANDROIDFRAMEWORKTEST_SQLIST_H

//
// Created by zzqni on 2024/4/17.
//

#ifndef ANDROIDFRAMEWORKTEST_SQSTACK_H
#define ANDROIDFRAMEWORKTEST_SQSTACK_H

#include "../common.h"


/**
 * 数组 栈
 */
struct SqStack {
    ElemType *base;
    ElemType *top;
    int stackSize;
};

int SqStack_Init(SqStack &s);

bool SqStack_IsEmpty(SqStack s);

int SqStack_GetLength(SqStack s);

Status SqStack_Clear(SqStack s);

Status SqStack_Destroy(SqStack &s);

Status SqStack_Push(SqStack &s, ElemType e);

Status SqStack_Pop(SqStack &s, ElemType &e);

Status SqStack_Peek(SqStack s, ElemType &e);

Status SqStack_Peek(SqStack s, int index, ElemType &e);

void SqStack_Create(SqStack &s, ElemType *array);

void SqStack_Print(SqStack s);

#endif //ANDROIDFRAMEWORKTEST_SQSTACK_H

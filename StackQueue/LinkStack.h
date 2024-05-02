//
// Created by zzqni on 2024/4/18.
//

#ifndef ANDROIDFRAMEWORKTEST_LINKSTACK_H
#define ANDROIDFRAMEWORKTEST_LINKSTACK_H

#include "../common.h"

/**
 * 链 栈
 * 头指针指向栈顶
 * 无头结点
 */
typedef struct StackNode {
    ElemType data;
    struct StackNode *next;
} StackNode, *LinkStack;

Status LinkStack_Init(LinkStack &s);

bool LinkStack_Empty(LinkStack s);

Status LinkStack_Push(LinkStack &s, ElemType e);

Status LinkStack_Pop(LinkStack &s, ElemType &e);

ElemType LinkStack_Peek(LinkStack s);

int LinkStack_GetLength(LinkStack s);

void LinkStack_Create(LinkStack &s, const ElemType *array);

void LinkStack_Print(LinkStack s);

#endif //ANDROIDFRAMEWORKTEST_LINKSTACK_H

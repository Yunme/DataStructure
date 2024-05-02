//
// Created by zzqni on 2024/4/18.
//

#ifndef ANDROIDFRAMEWORKTEST_SQQUEUE_H
#define ANDROIDFRAMEWORKTEST_SQQUEUE_H

#include "../common.h"
#include "commonSQ.h"

/**
 * 循环队列
 */
typedef struct {
    ElemType *base;
    int front; // 头
    int rear;  // 尾
} SqQueue;

Status SqQueue_Init(SqQueue &q);

int SqQueue_GetLength(SqQueue q);

bool SqQueue_IsEmpty(SqQueue q);

bool SqQueue_IsFull(SqQueue q);

Status SqQueue_Enqueue(SqQueue &q, ElemType e);

Status SqQueue_Dequeue(SqQueue &q, ElemType &e);

ElemType SqQueue_Peek(SqQueue q);

void SqQueue_Create(SqQueue &q, const ElemType *array);

void SqQueue_Print(SqQueue &q);

#endif //ANDROIDFRAMEWORKTEST_SQQUEUE_H

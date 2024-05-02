//
// Created by zzqni on 2024/4/18.
//

#ifndef ANDROIDFRAMEWORKTEST_LINKQUEUE_H
#define ANDROIDFRAMEWORKTEST_LINKQUEUE_H

#include "../common.h"
#include "commonSQ.h"

typedef struct QNode {
    ElemType data;
    struct QNode *next;
} QNode, *QueuePtr;

typedef struct {
    QueuePtr front;
    QueuePtr rear;
} LinkQueue;

Status LinkQueue_Init(LinkQueue &q);

void LinkQueue_Destroy(LinkQueue &q);

bool LinkQueue_IsEmpty(LinkQueue q);

void LinkQueue_Enqueue(LinkQueue &q, ElemType e);

Status LinkQueue_Dequeue(LinkQueue &q, ElemType &e);

Status LinkQueue_Peek(LinkQueue q, ElemType &e);

void LinkQueue_Create(LinkQueue &q, const ElemType *array);

void LinkQueue_Print(LinkQueue q);

#endif //ANDROIDFRAMEWORKTEST_LINKQUEUE_H

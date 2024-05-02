//
// Created by zzqni on 2024/4/18.
//

#include "SqQueue.h"
#include "commonSQ.h"

Status SqQueue_Init(SqQueue &q) {
    q.base = new ElemType[MAXQ_SIZE];
    if (!q.base)
        exit(OVERFLOW);
    q.front = q.rear = 0;
    return OK;
}

/**
 * 循环队列
 */
int SqQueue_GetLength(SqQueue q) {
    return (q.rear - q.front + MAXQ_SIZE) % MAXQ_SIZE;
}

/**
 * 队空
 */
bool SqQueue_IsEmpty(SqQueue q) {
    return q.front == q.rear;
}

bool SqQueue_IsFull(SqQueue q) {
    // 少用一个空间表示队满
    return (q.rear + 1) % MAXQ_SIZE == q.front;
}

/**
 * 入队
 */
Status SqQueue_Enqueue(SqQueue &q, ElemType e) {
    if (SqQueue_IsFull(q))
        return ERROR;
    q.base[q.rear] = e;
    q.rear = (q.rear + 1) % MAXQ_SIZE;
}

Status SqQueue_Dequeue(SqQueue &q, ElemType &e) {
    if (SqQueue_IsEmpty(q)) return ERROR;
    e = q.base[q.front];
    q.front = (q.front + 1) % MAXQ_SIZE;
    return OK;
}

ElemType SqQueue_Peek(SqQueue q) {
    if (SqQueue_IsEmpty(q))
        return '\0';
    return q.base[q.front];
}

void SqQueue_Create(SqQueue &q, const ElemType *array) {
    SqQueue_Init(q);
    while (*array != '\0') {
        SqQueue_Enqueue(q, *array);
        array++;
    }
}

void SqQueue_Print(SqQueue &q) {
    cout << '[';
    for (int i = 0; i < SqQueue_GetLength(q); ++i) {
        cout << q.base[(q.front + i) % MAXQ_SIZE];
        if (i != SqQueue_GetLength(q) - 1)
            cout << ", ";
    }
    cout << ']' << endl;
}
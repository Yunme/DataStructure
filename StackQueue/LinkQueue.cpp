//
// Created by zzqni on 2024/4/18.
//

#include "LinkQueue.h"

Status LinkQueue_Init(LinkQueue &q) {
    q.front = q.rear = new QNode;
    if (!q.front) exit(OVERFLOW);
    q.front->next = nullptr;
    return OK;
}

void LinkQueue_Destroy(LinkQueue &q) {
    QueuePtr p;
    while (q.front) {
        p = q.front->next;
        delete q.front;
        q.front = p;

        // 尾指针用来遍历
//        q.rear = q.front->next;
//        delete q.front;
//        q.front = q.rear;
    }
}

bool LinkQueue_IsEmpty(LinkQueue q) {
    return q.front == q.rear;
}

void LinkQueue_Enqueue(LinkQueue &q, ElemType e) {
    QueuePtr p = new QNode;
    p->data = e;
    p->next = nullptr;
    q.rear->next = p;
    q.rear = p;
}


Status LinkQueue_Dequeue(LinkQueue &q, ElemType &e) {
    if (LinkQueue_IsEmpty(q)) return ERROR;
    QueuePtr p = q.front->next;
    e = p->data;
    q.front->next = p->next;
    if (p == q.rear) {
        q.rear = q.front;
    }
    delete p;
    return OK;
}

Status LinkQueue_Peek(LinkQueue q, ElemType &e) {
    if (LinkQueue_IsEmpty(q)) return ERROR;
    e = q.front->next->data;
    return OK;
}

void LinkQueue_Create(LinkQueue &q, const ElemType *array) {
    LinkQueue_Init(q);
    while (*array != '\0') {
        LinkQueue_Enqueue(q, *array);
        array++;
    }
}

void LinkQueue_Print(LinkQueue q) {
    cout << '[';
    QueuePtr p = q.front->next;
    while (p) {
        cout << p->data;
        p = p->next;
        if (p)
            cout << ',';
    }
    cout << ']' << endl;
}

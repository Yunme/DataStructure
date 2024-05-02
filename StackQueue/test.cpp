//
// Created by zzqni on 2024/4/18.
//

#include "test.h"

void testStackQueue() {
//    testSqStack();
//    testLinkStack();
    testSqQueue();
//    testLinkQueue();
}

void testSqStack() {
    SqStack sqStack;
    SqStack_Init(sqStack);
    SqStack_Create(sqStack, "dcba");
    SqStack_Print(sqStack);

    SqStack_Push(sqStack, 'f');
    SqStack_Push(sqStack, 'f');
    SqStack_Push(sqStack, 'f');
    SqStack_Print(sqStack);

    ElemType e;
    SqStack_Pop(sqStack, e);
    SqStack_Print(sqStack);

    SqStack_Push(sqStack, 'o');
    SqStack_Peek(sqStack, e);
    SqStack_Pop(sqStack, e);
    SqStack_Pop(sqStack, e);

    SqStack_Print(sqStack);
    printf("peek %d: %c", 3, e);
}

void testLinkStack() {
    LinkStack linkStack;
    LinkStack_Init(linkStack);
    LinkStack_Create(linkStack, "olleh");
    LinkStack_Print(linkStack);
    LinkStack_Push(linkStack, ' ');
    LinkStack_Push(linkStack, 'd');
    LinkStack_Push(linkStack, 'l');
    LinkStack_Push(linkStack, 'r');
    LinkStack_Push(linkStack, 'o');
    LinkStack_Push(linkStack, 'w');
    LinkStack_Print(linkStack);
    int length = LinkStack_GetLength(linkStack);
    printf("length: %d\n", length);
    ElemType e;
    LinkStack_Pop(linkStack, e);
    printf("pop: %c\n", e);
    LinkStack_Print(linkStack);
}

void testSqQueue() {
    SqQueue sqQueue;
    SqQueue_Create(sqQueue, "abcde");
    SqQueue_Print(sqQueue);
    SqQueue_Enqueue(sqQueue, 'f');
    SqQueue_Enqueue(sqQueue, 'g');
    SqQueue_Enqueue(sqQueue, 'h');
    SqQueue_Enqueue(sqQueue, 'i');
    SqQueue_Enqueue(sqQueue, 'j');
    ElemType a;
    SqQueue_Dequeue(sqQueue, a);
    printf("dequeue: %c\n", a);
    SqQueue_Dequeue(sqQueue, a);
    printf("dequeue: %c\n", a);
    printf("front: %d, rear: %d\n", sqQueue.front, sqQueue.rear);
    SqQueue_Print(sqQueue);
    SqQueue_Dequeue(sqQueue, a);
    printf("dequeue: %c\n", a);
    SqQueue_Dequeue(sqQueue, a);
    printf("dequeue: %c\n", a);
    SqQueue_Dequeue(sqQueue, a);
    printf("dequeue: %c\n", a);
    SqQueue_Dequeue(sqQueue, a);
    printf("dequeue: %c\n", a);
    SqQueue_Print(sqQueue);
    SqQueue_Enqueue(sqQueue, 'k');
    SqQueue_Enqueue(sqQueue, 'l');
    printf("front: %d, rear: %d\n", sqQueue.front, sqQueue.rear);
    SqQueue_Print(sqQueue);
}

void testLinkQueue() {
    LinkQueue linkQueue;
    LinkQueue_Init(linkQueue);
    LinkQueue_Create(linkQueue, "abcde");
    LinkQueue_Print(linkQueue);
    LinkQueue_Enqueue(linkQueue, 'f');
    LinkQueue_Enqueue(linkQueue, 'g');
    LinkQueue_Enqueue(linkQueue, 'h');
    LinkQueue_Enqueue(linkQueue, 'i');
    LinkQueue_Enqueue(linkQueue, 'j');
    LinkQueue_Print(linkQueue);
    ElemType a;
    LinkQueue_Dequeue(linkQueue, a);
    printf("dequeue: %c\n", a);
    LinkQueue_Dequeue(linkQueue, a);
    printf("dequeue: %c\n", a);
    LinkQueue_Dequeue(linkQueue, a);
    printf("dequeue: %c\n", a);
    LinkQueue_Dequeue(linkQueue, a);
    printf("dequeue: %c\n", a);
    LinkQueue_Print(linkQueue);
    LinkQueue_Enqueue(linkQueue, 'k');
    LinkQueue_Enqueue(linkQueue, 'l');
    LinkQueue_Print(linkQueue);
}
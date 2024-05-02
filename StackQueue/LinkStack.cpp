//
// Created by zzqni on 2024/4/18.
//

#include "LinkStack.h"

Status LinkStack_Init(LinkStack &s) {
    s = nullptr;
    return OK;
}

bool LinkStack_Empty(LinkStack s) {
    return s == nullptr;
}

Status LinkStack_Push(LinkStack &s, ElemType e) {
    StackNode *p = new StackNode;
    p->data = e;
    p->next = s;
    s = p;
    return OK;
}

Status LinkStack_Pop(LinkStack &s, ElemType &e) {
    if (LinkStack_Empty(s))
        return ERROR;
    e = s->data;
    StackNode *p = s;
    s = s->next;
    delete p;
    return OK;
}

ElemType LinkStack_Peek(LinkStack s) {
    if (s)
        return s->data;
    return '\0';
}

int LinkStack_GetLength(LinkStack s) {
    int i = 0;
    while (s) {
        s = s->next;
        i++;
    }
    return i;
}

void LinkStack_Create(LinkStack &s, const ElemType *array) {
    while (*array != '\0') {
        LinkStack_Push(s, *array);
        array++;
    }
}

void LinkStack_Print(LinkStack s) {
    cout << '[';
    while (s) {
        cout << s->data;
        s = s->next;
        if (s)
            cout << ", ";
    }
    cout << ']' << endl;
}
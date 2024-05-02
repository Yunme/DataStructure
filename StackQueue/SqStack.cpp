//
// Created by zzqni on 2024/4/17.
//

#include <cstdlib>
#include "SqStack.h"

int SqStack_Init(SqStack &s) {
    s.base = new ElemType[MAXSIZE];
    if (!s.base)
        exit(OVERFLOW);
    s.top = s.base;
    s.stackSize = MAXSIZE;
    return OK;
}

bool SqStack_IsEmpty(SqStack s) {
    return s.top == s.base;
}

int SqStack_GetLength(SqStack s) {
    return s.top - s.base;
}

Status SqStack_Clear(SqStack s) {
    if (s.base) s.top = s.base;
    return OK;
}

Status SqStack_Destroy(SqStack &s) {
    if (s.base) {
        delete s.base;
        s.stackSize = 0;
        s.base = s.top = nullptr;
    }
    return OK;
}

Status SqStack_Push(SqStack &s, ElemType e) {
    if (s.top - s.base == s.stackSize)
        return ERROR;
    *s.top++ = e;
}

Status SqStack_Pop(SqStack &s, ElemType &e) {
    if (SqStack_IsEmpty(s))
        return ERROR;
    e = *--s.top;
}

Status SqStack_Peek(SqStack s, ElemType &e) {
    if (SqStack_IsEmpty(s))
        return ERROR;
    e = *(s.top - 1);
    return OK;
}

Status SqStack_Peek(SqStack s, int index, ElemType &e) {
    if (index < 0 && index >= s.stackSize)
        return ERROR;
    e = *(s.top - 1 - index);
    return OK;
}

void SqStack_Create(SqStack &s, ElemType *array) {
    while (*array != '\0') {
        SqStack_Push(s, *array);
        array++;
    }
}

void SqStack_Print(SqStack s) {
    int length = SqStack_GetLength(s);
    for (int i = 0; i < length; ++i) {
        ElemType a;
        SqStack_Peek(s, i, a);
        cout << a;
        if (i != length - 1)
            cout << ',' << ' ';
    }
    cout << endl;
}


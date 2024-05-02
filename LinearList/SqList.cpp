// Created by zzqni on 2024/4/16.
#include <cstdlib>
#include <iostream>
#include "SqList.h"


int InitList_Sq(SqList &L) {
    L.elem = new ElemType[MAXSIZE];
    if (!L.elem)
        exit(OVERFLOW);
    L.length = 0;
    return OK;
}

void DestroyList(SqList &L) {
    if (L.elem) delete L.elem;
}

void ClearList(SqList &L) {
    L.length = 0;
}

int GetLength(SqList L) {
    return L.length;
}

int isEmpty(SqList L) {
    if (L.length == 0) return 1;
    return 0;
}

// 随机取值
int GetElem(SqList L, int i, ElemType &e) {
    if (i < 1 || i > L.length) return ERROR;
    e = L.elem[i - 1];
    return OK;
}

// 按值查找
int LocateElem(SqList L, ElemType e) {
    for (int i = 0; i < L.length; ++i) {
        if (L.elem[i] == e) return i + 1;
    }
    return 0;
}

// 插入元素
Status ListInsert_Sq(SqList &L, int i, ElemType e) {
    if (i < 1 || i - 1 > L.length) return ERROR;
    if (L.length == MAXSIZE) return ERROR;
    // i 后面的后移一位
    for (int j = L.length - 1; j >= i - 1; j--) {
        L.elem[j + 1] = L.elem[j];
    }
    L.elem[i - 1] = e;
    L.length++;
    return OK;
}

// 删除元素
Status ListDelete_Sq(SqList &L, int i) {
    if (i < 1 || i > L.length) return ERROR;
    for (int j = i; j < L.length; ++j) {
        L.elem[j - 1] = L.elem[j];
    }
    L.length--;
    return OK;
}

void ListSq_Print(SqList L) {
    std::cout << '[';
    for (int i = 0; i <= L.length - 1; ++i) {
        char a;
        GetElem(L, i + 1, a);
        std::cout << a;
        if (i != L.length - 1)
            std::cout << ',' << ' ';
    }
    std::cout << ']' << std::endl;
}

void ListSq_Create(SqList &L, ElemType *array) {
    InitList_Sq(L);
    for (int i = 1; *array != '\0'; ++i, array++) {
        ListInsert_Sq(L, i, *array);
    }
}
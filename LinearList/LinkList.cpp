//
// Created by zzqni on 2024/4/16.
//

#include "LinkList.h"
#include <iostream>

Status InitList_L(LinkList &L) {
    L = new LinkNode;
    L->next = nullptr;
    return OK;
}

int ListEmpty_L(LinkList L) {
    if (L->next) {
        return 0;
    }
    return 1;
}

Status DestroyList_L(LinkList &L) {
    LinkNode *p;
    while (L) {
        p = L;
        L = L->next;
        delete p;
    }
    return OK;
}

// 头保留
int ClearList_L(LinkList &L) {
    LinkNode *p = L->next, *q;
    while (p) {
        q = p->next;
        delete p;
        p = q;
    }
    L->next = nullptr;
    return OK;
}

int GetLength_L(LinkList L) {
    if (!L) {
        return -1;
    }
    LinkNode *p = L->next;
    int i = 0;
    while (p) {
        i++;
        p = p->next;
    }
    return i;
}

int GetElem_L(LinkList L, int i, ElemType &e) {
    LinkNode p;
    if (GetElem_L(L, i, p)) {
        e = p.data;
        return OK;
    }
    return ERROR;
}

LinkNode *LocateElem_L(LinkList L, ElemType e) {
    LinkNode *p = L->next;
    while (p && p->data != e) {
        p = p->next;
    }
    return p;
}

Status GetElem_L(LinkList L, int index, LinkNode &node) {
    LinkNode *p = L->next;
    int j = 1;
    while (j < index && p) {
        p = p->next;
        j++;
    }
    if (!p || j > index) return ERROR;
    node = *p;
    return OK;
}


int LocateElemIndex_L(LinkList L, ElemType e) {
    LinkNode *p = L->next;
    int i = 1;
    while (p && p->data != e) {
        i++;
        p = p->next;
    }
    if (p)
        return i;
    return 0;
}

// index:(1 ~ n+1)
int InsertNode_L(LinkList &L, int index, ElemType e) {
    LinkNode *p = L;
    int j = 0;
    while (p && j < index - 1) {
        p = p->next;
        j++;
    }
    if (!p || j > index - 1)
        return ERROR;
    auto *s = new LinkNode;
    s->data = e;
    s->next = p->next;
    p->next = s;
    return OK;
}

int DeleteNode_L(LinkList &L, int index, ElemType &e) {
    LinkNode *p = L;
    int j = 0;
    while (p->next && j < index - 1) {
        p = p->next;
        j++;
    }
    if (!(p->next) || j > index - 1)
        return ERROR;
    LinkNode *current = p->next;
    e = p->data;
    p->next = current->next;
    delete current;
    return OK;

//    if (L == nullptr || index <= 0) {
//        return ERROR;
//    }
//
//    int i = 1;
//    LinkNode * prev = nullptr;
//    LinkNode* current = L;
//    while (current != nullptr && i < index) {
//        prev = current;
//        current = current->next;
//        i++;
//    }
//
//    if (current == nullptr) {
//        return ERROR;
//    }
//
//    if (prev == nullptr) {
//        L = current->next;
//    } else {
//        prev->next = current->next;
//    }
//
//    delete current;
//    return OK;
}

// 头插法创建链表
void CreateList_H(LinkList &L, int n) {
    L = new LinkNode;
    L->next = nullptr;
    for (int i = n; i > 0; i--) {
        LinkNode *p = new LinkNode;
        cin >> p->data;
        p->next = L->next;
        L->next = p;
    }
}

// 尾插法 创建链表
void CreateList_T(LinkList &L, int n) {
    L = new LinkNode;
    L->next = nullptr;
    LinkNode *t = L;
    for (int i = 0; i < n; i++) {
        LinkNode *p = new LinkNode;
        p->next = nullptr;
        cin >> p->data;
        t->next = p;
        t = p;
    }
}

void CreateList_Array(LinkList &L, ElemType *array) {
    L = new LinkNode;
    L->next = nullptr;
    LinkNode *t = L;
    while (*array != '\0') {
        LinkNode *p = new LinkNode;
        p->next = nullptr;
        p->data = *array;
        t->next = p;
        t = p;
        array++;
    }
}

void LinkList_Print(LinkList L) {
    LinkNode *p = L->next;
    while (p) {
        cout << p->data;
        p = p->next;
        if (p) {
            cout << ',' << ' ';
        }
    }
    cout << endl;
}


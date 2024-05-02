//
// Created by zzqni on 2024/4/17.
//

#include "DuLinkList.h"

DuLNode *GetElemP_DuL(DuLinkList &L, int i) {
    DuLNode *p = L->next;
    int j = 1;
    while (p && j < i) {
        p = p->next;
        j++;
    }
    if (!p || j > i) {
        return nullptr;
    }
    return p;
}

Status ListInsert_Dul(DuLinkList &L, int i, ElemType e) {
    DuLNode *p = GetElemP_DuL(L, i);
    if (!p)
        return ERROR;
    DuLNode *s = new DuLNode;
    s->data = e;
    s->prior = p->prior;
    s->next = p;
    p->prior->next = s;
    p->prior = s;
    return OK;
}

Status ListDelete_Dul(DuLinkList &L, int i, ElemType &e) {
    DuLNode *p = GetElemP_DuL(L, i);
    if (!p)
        return ERROR;
    e = p->data;
    p->prior->next = p->next;
    p->next->prior = p->prior;
    delete p;
    return OK;
}


void CreateDuLinkList_Array(DuLinkList &L, ElemType *array) {
    L = new DuLNode;
    L->prior = nullptr;
    L->next = nullptr;
    DuLNode *prev = L;
    DuLNode *current;
    while (*array != '\0') {
        DuLNode *p = new DuLNode;
        p->next = nullptr;
        p->data = *array;

        current = p;
        current->next = nullptr;
        current->prior = prev;

        prev->next = current;
        prev = current;
        array++;
    }
}

void DuLinkList_Print(DuLinkList L) {
    DuLNode *p = L->next;
    while (p) {
        cout << p->data;
        p = p->next;
        if (p) {
            cout << ',' << ' ';
        }
    }
    cout << endl;
}

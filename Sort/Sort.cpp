//
// Created by zzqni on 2024/5/1.
//

#include "Sort.h"

void SortPrint(const SortSqList &list) {
    for (int i = 0; i < list.length; ++i) {
        if (i != 0) printf(",");
        printf("%d", list.r[i].key);
    }
    printf("\n");
}

SortLinkList SortSq_Link(const SortSqList &list) {
    if (list.length <= 0) return nullptr;
    auto *head = new SortNode(list.r[0]);
    SortNode *p = head;
    for (int i = 1; i < list.length; ++i) {
        p->next = new SortNode(list.r[i]);
        p = p->next;
    }
    return head;
}

void SortPrint(const SortLinkList &list) {
    SortNode *p = list;
    while (p) {
        printf("%d", p->val.key);
        p = p->next;
        if (p) printf(",");
    }
    printf("\n");
}

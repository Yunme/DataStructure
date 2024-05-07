//
// Created by zzqni on 2024/5/1.
//

#ifndef ANDROIDFRAMEWORKTEST_SORT_H
#define ANDROIDFRAMEWORKTEST_SORT_H

#include <utility>

#include "../common.h"

typedef struct {
    ElementType r[MAXSIZE];
    int length;
} SortSqList;

typedef struct SortNode {
    ElementType val;
    SortNode *next;
    SortNode() : val(0), next(nullptr) {}
    SortNode(ElementType x) : val(std::move(x)), next(nullptr) {}
    SortNode(ElementType x, SortNode *next) : val(std::move(x)), next(next) {}
} SortNode, *SortLinkList;

void SortPrint(const SortSqList &list);

SortLinkList SortSq_Link(const SortSqList &list);

void SortPrint(const SortLinkList &list);

#endif //ANDROIDFRAMEWORKTEST_SORT_H

//
// Created by zzqni on 2024/5/1.
//

#ifndef ANDROIDFRAMEWORKTEST_SORT_H
#define ANDROIDFRAMEWORKTEST_SORT_H

#include "../common.h"

typedef struct {
    ElementType r[MAXSIZE];
    int length;
} SqList;

void SortPrint(const SqList &list);

#endif //ANDROIDFRAMEWORKTEST_SORT_H

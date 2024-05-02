//
// Created by zzqni on 2024/5/1.
//

#ifndef ANDROIDFRAMEWORKTEST_RADIXSORT_H
#define ANDROIDFRAMEWORKTEST_RADIXSORT_H

#include "Sort.h"

#define MAXNUM_KEY 8
#define RADIX 10
#define MAX_SPACE 10000

typedef struct {
    KeyType keys[MAXNUM_KEY];
    int next;
} SLCell;

typedef struct {
    SLCell r[MAX_SPACE];
    int keyNum;
    int recordNum;
} SLList;

typedef int ArrType[RADIX];

void RadixSort(SLList &L);

void RadixPrint(const SLList &L);

void radixSort(vector<ElementType> &arr);

#endif //ANDROIDFRAMEWORKTEST_RADIXSORT_H

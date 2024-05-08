//
// Created by zzqni on 2024/5/1.
//

#ifndef ANDROIDFRAMEWORKTEST_SELECTIONSORT_H
#define ANDROIDFRAMEWORKTEST_SELECTIONSORT_H

#include "Sort.h"

void Sort_SelectionSimple(SortSqList &list);

void Sort_SelectionHeap(SortSqList &list);

void Sort_MergeSort(SortSqList &list, int low, int high);

void Sort_MergeSortLinkList(SortLinkList &list);

void Sort_MergeSortLinkListUseLoop(SortLinkList &list);

#endif //ANDROIDFRAMEWORKTEST_SELECTIONSORT_H

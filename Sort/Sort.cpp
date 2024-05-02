//
// Created by zzqni on 2024/5/1.
//

#include "Sort.h"

void SortPrint(const SqList &list) {
    for (int i = 0; i < list.length; ++i) {
        if (i != 0) printf(",");
        printf("%d", list.r[i].key);
    }
    printf("\n");
}
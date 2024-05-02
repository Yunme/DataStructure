//
// Created by zzqni on 2024/5/1.
//

#include "SwapSort.h"

/**
 * ������ð������
 */
void Sort_SwapBubble(SqList &list) {
    int totalCompare = 0;
    for (int i = 0; i < list.length - 1; ++i) {
        bool swapped = false;
        for (int j = 0; j < list.length - i - 1; ++j) {
            printf("Ԫ�� %d �� Ԫ�� %d �Ƚ�\n", list.r[j].key, list.r[i].key);
            totalCompare++;
            if (list.r[j].key > list.r[j + 1].key) {
                ElementType temp = list.r[j + 1];
                list.r[j + 1] = list.r[j];
                list.r[j] = temp;
                swapped = true;
            }
            SortPrint(list);
        }
        if (!swapped) break;
    }
    printf("�ܹ��Ƚ�%d��\n", totalCompare);
}

/**
 * �������������� ����
 */
int Sort_SwapQuickPartition(SqList &list, int low, int high) {
    ElementType data = list.r[low];
    KeyType pivotKey = list.r[low].key;
    while (low < high) {
        while (low < high && list.r[high].key >= pivotKey)
            --high;
        list.r[low] = list.r[high];

        while (low < high && list.r[low].key <= pivotKey)
            ++low;
        list.r[high] = list.r[low];
    }
    list.r[low] = data;
    return low;
}

/**
 * ��������������
 */
void Sort_SwapQuick(SqList &list, int low, int high) {
    if (low < high) {
        int pivotPos = Sort_SwapQuickPartition(list, low, high);

        Sort_SwapQuick(list, low, pivotPos - 1);
        Sort_SwapQuick(list, pivotPos + 1, high);
    }
}

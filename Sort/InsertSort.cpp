//
// Created by zzqni on 2024/5/1.
//

#include "InsertSort.h"

/**
 * ֱ�Ӳ�������
 * �Ӻ���ǰ���� + �ƶ�
 */
void Sort_InsertStraight(SqList &list) {
    if (list.length <= 1) return;
    int totalCompare = 0;
    for (int i = 1; i < list.length; ++i) {
        ElementType data = list.r[i];
        printf("Ԫ�أ�%d ", data.key);
        int j;
        if (data.key < list.r[i - 1].key) {
            for (j = i - 1; j >= 0 && data.key < list.r[j].key; --j) {
                list.r[j + 1] = list.r[j];
            }
            totalCompare += i - 1 - j;
            printf("�Ƚ���%d�Σ��ҵ�λ�ã�%d\n", (i - 1 - j), j + 1);
            list.r[j + 1] = data;
        } else {
            printf("����Ҫ�ƶ�\n");
        }
        SortPrint(list);
    }
    printf("�ܹ��Ƚ�%d��\n", totalCompare);
}

/**
 * ֱ�Ӳ�������
 * ��ǰ������
 * �ƶ�
 */
void Sort_InsertStraightBackward(SqList &list) {
    if (list.length <= 1) return;
    int totalCompare = 0;
    for (int i = 1; i < list.length; ++i) {
        printf("Ԫ�أ�%d ", list.r[i].key);
        ElementType data = list.r[i];
        if (data.key < list.r[i - 1].key) {
            int j;
            for (j = 0; j < i; ++j) {
                if (list.r[j].key > data.key) {
                    totalCompare += j + 1;
                    printf("�Ƚ���%d�Σ��ҵ�λ�ã�%d\n", j + 1, j);
                    break;
                }
            }
            for (int k = i; k > j; --k) {
                list.r[k] = list.r[k - 1];
            }
            list.r[j] = data;
            SortPrint(list);
        } else {
            printf("����Ҫ�ƶ�\n");
        }
    }
    printf("�ܹ��Ƚ�%d��\n", totalCompare);
}

/**
 * ���ֲ�������
 */
void Sort_InsertBinary(SqList &list) {
    if (list.length <= 1) return;
    int totalCompare = 0;
    for (int i = 1; i < list.length; ++i) {
        int low = 0, high = i - 1;
        ElementType data = list.r[i];
        int compare = 0;
        while (low <= high) {
            compare++;
            int mid = (low + high) / 2;
            if (data.key < list.r[mid].key)
                high = mid - 1;
            else
                low = mid + 1;
        }
        totalCompare += compare;
        printf("Ԫ�أ�%d �Ƚ���%d�� �ҵ�λ�ã�%d\n", data.key, compare, high + 1);
        for (int j = i - 1; j >= high + 1; --j) {
            list.r[j + 1] = list.r[j];
        }
        list.r[high + 1] = data;
        SortPrint(list);
    }
    printf("�ܹ��Ƚ�%d��\n", totalCompare);
}

void Sort_InsertShell(SqList &list) {
    int maxK = 0;
    // Hibbard ���� 2^k - 1
    while ((1 << maxK) - 1 < list.length) {
        maxK++;
    }
    maxK--;
    for (int k = maxK; k >= 0; --k) {
        int gap = (1 << k) - 1;
        for (int i = gap; i < list.length; i++) {
            if (list.r[i].key < list.r[i - gap].key) {
                ElementType data = list.r[i];
                int j;
                for (j = i - gap; j >= 0 && data.key < list.r[j].key; j -= gap) {
                    list.r[j + gap] = list.r[j];
                }
                list.r[j + gap] = data;
                SortPrint(list);
            }
        }
    }
}
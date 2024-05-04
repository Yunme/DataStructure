//
// Created by zzqni on 2024/5/1.
//

#include "SelectionSort.h"

/**
 * ��ѡ������
 */
void Sort_SelectionSimple(SortSqList &list) {
    for (int i = 0; i < list.length; ++i) {
        int minPos = i;
        for (int j = i + 1; j < list.length; ++j) {
            if (list.r[j].key < list.r[minPos].key) {
                minPos = j;
            }
        }
        printf("�ҵ���%d��ʼ��СԪ��%d\n", i, list.r[minPos].key);
        if (minPos != i) {
            ElementType temp = list.r[minPos];
            list.r[minPos] = list.r[i];
            list.r[i] = temp;
        }
        SortPrint(list);
    }
}

/**
 * ������
 * �����ѣ������Ա��� start-length �е�Ԫ��
 * �����
 */
void Sort_HeapAdjust(SortSqList &list, int start, int length) {
    ElementType data = list.r[start];
    for (int i = 2 * start + 1; i < length; i = 2 * i + 1) {
        if (i < length - 1 && list.r[i].key < list.r[i + 1].key)
            i++;
        if (list.r[i].key <= data.key)
            break;
        list.r[start] = list.r[i];
        start = i;
    }
    list.r[start] = data;
}

void Sort_SelectionHeap(SortSqList &list) {
    // ��������� �����һ����Ҷ�ӽ����ǰ�����ɶ�
    for (int i = list.length / 2 - 1; i >= 0; --i) {
        Sort_HeapAdjust(list, i, list.length);
    }
    // �𲽽��Ѷ�Ԫ��������һ��Ԫ�ؽ�������С��Χ ��������
    for (int i = list.length - 1; i > 0; --i) {
        ElementType data = list.r[i];
        list.r[i] = list.r[0];
        list.r[0] = data;
        Sort_HeapAdjust(list, 0, i);
    }
}

/**
 * �鲢����
 */
void Sort_Merge(SortSqList &list, int low, int mid, int high) {
    int n1 = mid - low + 1;
    int n2 = high - mid;
    //������ʱ�������洢���������ֵ�Ԫ��
    SortSqList sqList1, sqList2;
    sqList1.length = n1;
    sqList2.length = n2;
    for (int i = 0; i < n1; ++i) {
        sqList1.r[i] = list.r[low + i];
    }
    for (int i = 0; i < n2; ++i) {
        sqList2.r[i] = list.r[mid + 1 + i];
    }
    // �鲢�������������鵽ԭ����
    int i = 0; // ��벿�����������
    int j = 0; // �Ұ벿�����������
    int k = low; // ԭ���������

    while (i < n1 && j < n2) {
        if (sqList1.r[i].key <= sqList2.r[j].key) {
            list.r[k++] = sqList1.r[i++];
        } else {
            list.r[k++] = sqList2.r[j++];
        }
    }

    // ��ʣ���Ԫ�ع鲢��ԭ����
    while (i < n1) {
        list.r[k++] = sqList1.r[i++];
    }
    while (j < n2) {
        list.r[k++] = sqList2.r[j++];
    }
}

void Sort_MergeSort(SortSqList &list, int low, int high) {
    if (low < high) {
        int mid = (low + high) / 2;
        Sort_MergeSort(list, low, mid);
        Sort_MergeSort(list, mid + 1, high);

        Sort_Merge(list, low, mid, high);
    }
}

/**
* ��������
*/
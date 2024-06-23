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
 * �����ѣ������ ��������
 * �����Ա��� start-length �е�Ԫ�ص�����������������
 */
void Sort_HeapAdjust(SortSqList &list, int start, int length) {
    ElementType data = list.r[start];
    // ���� 2 * start + 1
    for (int i = 2 * start + 1; i < length; i = 2 * i + 1) {
        // �ҳ����Һ����еĽϴ���
        // �Һ��� = i + 1
        if (i < length - 1 && list.r[i].key < list.r[i + 1].key)    // �������С���Һ���
            i++;
        // ��ô�Һ��ӽϴ�
        if (list.r[i].key <= data.key)  // �ϴ�ĺ��Ӳ����ڸ���� ����Ҫ���� ��������
            break;
        // �ϴ�ĺ��ӱ�ɸ��ڵ�
        list.r[start] = list.r[i];
        // �� i ��������һ�ֵ���, ��ֵ���� data
        start = i;
    }
    // ��� data ��ֵ����ǰλ��
    list.r[start] = data;
}

/**
 * ���� �� i ���Ϊ�������Ӷѣ�
 * �ݹ鷨
 * @param i �� i ����Ԫ�ؽ��е��������ݹ�ĵ������ĺ���
 */
void Sort_HeapAdjust2(SortSqList &list, int i, int n) {
    // �ҳ� ���Һ����� �ȸ�����Ľϴ��ߣ��������㽻��
    int bigger = i;
    int lc = 2 * i + 1;
    int rc = 2 * i + 2;
    // ��� ���ӽϴ�
    if (lc < n && list.r[bigger].key < list.r[lc].key) {
        // ����Ϊ����
        bigger = lc;
    }
    // ��� �Һ��ӽϴ�
    if (rc < n && list.r[bigger].key < list.r[rc].key) {
        // ����Ϊ�Һ���
        bigger = rc;
    }
    // ����ϴ�ֵ ���Ǹ���㣬����Ҫ����
    if (bigger != i) {
        // �����������ϴ���
        swap(list.r[bigger], list.r[i]);
        // �ݹ������������ӽڵ�
        Sort_HeapAdjust2(list, n, bigger);
    }
}

/**
 * ���������
 * �ѣ�
 * �±� i �����ӣ�2 * i + 1, �Һ��ӣ�2 * i + 2;
 * �±� i �ĸ��ڵ㣺(i - 1) / 2
 * 1. ���������
 *    �����һ����Ҷ�ӽ����ǰ�����ɶ�
 *    ������ȫ�������Ķ��壺���һ����Ҷ�ӽ��� = ���һ�����ĸ��ڵ�
 *    ���һ����� n - 1��(n - 1 - 1) / 2 = n / 2 - 1
 * 2. �������㽻������
 *    ���ݴ�������ʣ�������������������ġ�
 *    �����һ����������㽻���������Ѿ��������
 *    ��������������ѣ��������һ����㲻���Ƕѵķ�Χ��
 */
void Sort_SelectionHeap(SortSqList &list) {
    // ��������� �����һ����Ҷ�ӽ����ǰ�����ɶ�
    // Ҷ�ӽ�㲻��Ҫ�������Ѿ�����ѵ�����
    // ���һ����Ҷ�ӽ��������ǣ�n / 2 - 1
    for (int i = list.length / 2 - 1; i >= 0; --i) {
        Sort_HeapAdjust2(list, i, list.length);
    }
    // ���ݴ�������ʣ������϶��������������ġ�
    // �𲽽��Ѷ�Ԫ��������һ��Ԫ�ؽ�����ÿ����һ�Σ�����ֵ�͵�����ˡ�����
    for (int i = list.length - 1; i > 0; --i) {
//        ElementType data = list.r[i];
//        list.r[i] = list.r[0];
//        list.r[0] = data;
        swap(list.r[0], list.r[i]);
        // ��������
//        Sort_HeapAdjust(list, 0, i);
//
        // �ݹ����
        Sort_HeapAdjust2(list, 0, i); // �����ڱ�С������Ĳ���Ҫ�ٲ��������
    }
}

/**
 * �鲢���� ����˳���汾
 * ���������������ϵ����������й鲢��һ����������
 */
void Sort_Merge(SortSqList &list, int low, int mid, int high) {
    // [low, mid] ��벿�� ����mid
    int n1 = mid - low + 1;
    // (mid, high] �Ұ벿��
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
        // ǰ�벿��
        Sort_MergeSort(list, low, mid);
        // ��벿��
        Sort_MergeSort(list, mid + 1, high);

        Sort_Merge(list, low, mid, high);
    }
}

/**
 * �鲢������������汾
 * @param list
 */
void Sort_MergeSortIteration(SortSqList &list) {
    // �Ӳ���Ϊ 1 ��ʼ���й鲢�����������𽥼ӱ�
    for (int size = 1; size < list.length; size *= 2) {
        for (int i = 0; i < list.length - size; i += 2 * size) {
            // [low, mid] ��벿�� ����mid
            int low = i;
            int mid = low + size - 1;
            // (mid, high] �Ұ벿��
            int high = min(low + 2 * size - 1, list.length - 1);
            // �ϲ���������������
            Sort_Merge(list, low, mid, high);
        }
    }
}

/**
 * �鲢���� ����汾
 * ʱ�� nlogN
 * �ռ� logN �ݹ�ջ
 * ���������������ϵ����������й鲢��һ����������
 */
SortNode *findMid(SortNode *head) {
    if (head == nullptr || head->next == nullptr) return head;
    SortNode *slow = head, *fast = head;
    while (fast->next && fast->next->next) {
        slow = slow->next;
        fast = fast->next->next;
    }
    return slow;
}

SortNode *Sort_MergeLink(SortNode *low, SortNode *midNext) {
    if (low == nullptr) return midNext;
    if (midNext == nullptr) return low;
    SortNode *p1 = low;
    SortNode *p2 = midNext;
    SortNode *dummyNode = new SortNode;
    SortNode *p = dummyNode;
    // �ϲ�������������
    while (p1 && p2) {
        if (p1->val.key < p2->val.key) {
            p->next = p1;
            p1 = p1->next;
        } else {
            p->next = p2;
            p2 = p2->next;
        }
        p = p->next;
    }
    p->next = p1 ? p1 : p2;
    SortNode *result = dummyNode->next;
    delete dummyNode;
    return result;
}

// �ݹ�ֱ��ʣ����Ԫ�رȽϴ�С�� �鲢���ϲ���������
void Sort_MergeSortLinkList(SortLinkList &list) {
    if (list == nullptr || list->next == nullptr) return;
    // ��ʼ
    SortNode *low = list;
    // �м�
    SortNode *mid = findMid(list);
    SortNode *midNext = mid->next;
    // �м�next �ÿգ����жϿ���
    mid->next = nullptr;

    // �󲿷�
    Sort_MergeSortLinkList(low);
    // �Ҳ���
    Sort_MergeSortLinkList(midNext);

    // �ϲ���������
    list = Sort_MergeLink(low, midNext);
}


/**
 * �鲢���� ����汾
 * ʱ�� nlogN
 * �ռ� ����
 * ���������������ϵ����������й鲢��һ����������
 */
/**
 * ��ͷ��ʼ�ĵ� size ����Ͽ�����������ʣ�µ�
 */
SortNode *Sort_subLinkList(SortLinkList list, int size) {
    if (list == nullptr) return list;
    for (int i = 1; i < size && list->next; ++i) {
        list = list->next;
    }
    SortNode *remain = list->next;
    list->next = nullptr;
    return remain;
}

void Sort_MergeSortLinkListUseLoop(SortLinkList &list) {
    // ����
    int len = 0;
    SortNode *p = list;
    while (p) {
        p = p->next;
        len++;
    }
    auto *dummy = new SortNode;
    dummy->next = list;
    for (int size = 1; size < len; size *= 2) {
        SortNode *current = dummy->next;
        SortNode *prev = dummy;
        while (current) {
            SortNode *leftHead = current;

            // ����ʼ�� size ���ָ�
            SortNode *rightHead = Sort_subLinkList(leftHead, size);
            // ���ҿ�ʼ�� size ���ָ�
            // current ����
            current = Sort_subLinkList(rightHead, size);
            // �ϲ������֮ǰ����
            SortNode *merged = Sort_MergeLink(leftHead, rightHead);
            prev->next = merged;

            // prev ָ����Ƶ��ϲ�֮���ĩβ����ʼ�´�ѭ��
            while (prev->next) {
                prev = prev->next;
            }
        }
    }
    list = dummy->next;
}
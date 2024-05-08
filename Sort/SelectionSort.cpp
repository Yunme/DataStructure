//
// Created by zzqni on 2024/5/1.
//

#include "SelectionSort.h"

/**
 * 简单选择排序
 */
void Sort_SelectionSimple(SortSqList &list) {
    for (int i = 0; i < list.length; ++i) {
        int minPos = i;
        for (int j = i + 1; j < list.length; ++j) {
            if (list.r[j].key < list.r[minPos].key) {
                minPos = j;
            }
        }
        printf("找到从%d开始最小元素%d\n", i, list.r[minPos].key);
        if (minPos != i) {
            ElementType temp = list.r[minPos];
            list.r[minPos] = list.r[i];
            list.r[i] = temp;
        }
        SortPrint(list);
    }
}

/**
 * 堆排序
 * 调整堆，将线性表中 start-length 中的元素
 * 大根堆
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
    // 创建大根堆 从最后一个非叶子结点向前调整成堆
    for (int i = list.length / 2 - 1; i >= 0; --i) {
        Sort_HeapAdjust(list, i, list.length);
    }
    // 逐步将堆顶元素与堆最后一个元素交换，缩小范围 并调整堆
    for (int i = list.length - 1; i > 0; --i) {
        ElementType data = list.r[i];
        list.r[i] = list.r[0];
        list.r[0] = data;
        Sort_HeapAdjust(list, 0, i);
    }
}

/**
 * 归并排序 数组顺序表版本
 * 将两个或两个以上的有序子序列归并成一个有序序列
 */
void Sort_Merge(SortSqList &list, int low, int mid, int high) {
    // [low, mid] 左半部分 包含mid
    int n1 = mid - low + 1;
    // (mid, high] 右半部分
    int n2 = high - mid;
    //创建临时数组来存储左右两部分的元素
    SortSqList sqList1, sqList2;
    sqList1.length = n1;
    sqList2.length = n2;
    for (int i = 0; i < n1; ++i) {
        sqList1.r[i] = list.r[low + i];
    }
    for (int i = 0; i < n2; ++i) {
        sqList2.r[i] = list.r[mid + 1 + i];
    }
    // 归并左右两部分数组到原数组
    int i = 0; // 左半部分数组的索引
    int j = 0; // 右半部分数组的索引
    int k = low; // 原数组的索引

    while (i < n1 && j < n2) {
        if (sqList1.r[i].key <= sqList2.r[j].key) {
            list.r[k++] = sqList1.r[i++];
        } else {
            list.r[k++] = sqList2.r[j++];
        }
    }

    // 将剩余的元素归并到原数组
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
        // 前半部分
        Sort_MergeSort(list, low, mid);
        // 后半部分
        Sort_MergeSort(list, mid + 1, high);

        Sort_Merge(list, low, mid, high);
    }
}

/**
 * 归并排序 链表版本
 * 时间 nlogN
 * 空间 logN 递归栈
 * 将两个或两个以上的有序子序列归并成一个有序序列
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
    // 合并两个有序链表
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

// 递归直到剩单个元素比较大小后， 归并（合并有序链表）
void Sort_MergeSortLinkList(SortLinkList &list) {
    if (list == nullptr || list->next == nullptr) return;
    // 起始
    SortNode *low = list;
    // 中间
    SortNode *mid = findMid(list);
    SortNode *midNext = mid->next;
    // 中间next 置空，从中断开。
    mid->next = nullptr;

    // 左部分
    Sort_MergeSortLinkList(low);
    // 右部分
    Sort_MergeSortLinkList(midNext);

    // 合并有序链表
    list = Sort_MergeLink(low, midNext);
}


/**
 * 归并排序 链表版本
 * 时间 nlogN
 * 空间 常数
 * 将两个或两个以上的有序子序列归并成一个有序序列
 */
/**
 * 从头开始的第 size 个后断开链表，并返回剩下的
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
    // 长度
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

            // 从左开始的 size 个分割
            SortNode *rightHead = Sort_subLinkList(leftHead, size);
            // 从右开始的 size 个分割
            // current 后移
            current = Sort_subLinkList(rightHead, size);
            // 合并后的与之前相连
            SortNode *merged = Sort_MergeLink(leftHead, rightHead);
            prev->next = merged;

            // prev 指针后移到合并之后的末尾，开始下次循环
            while (prev->next) {
                prev = prev->next;
            }
        }
    }
    list = dummy->next;
}
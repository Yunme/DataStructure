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
 * 调整堆，大根堆 迭代做法
 * 将线性表中 start-length 中的元素调整成满足大根堆性质
 */
void Sort_HeapAdjust(SortSqList &list, int start, int length) {
    ElementType data = list.r[start];
    // 左孩子 2 * start + 1
    for (int i = 2 * start + 1; i < length; i = 2 * i + 1) {
        // 找出左右孩子中的较大者
        // 右孩子 = i + 1
        if (i < length - 1 && list.r[i].key < list.r[i + 1].key)    // 如果左孩子小于右孩子
            i++;
        // 那么右孩子较大
        if (list.r[i].key <= data.key)  // 较大的孩子不大于父结点 则不需要调整 满足大根堆
            break;
        // 较大的孩子变成父节点
        list.r[start] = list.r[i];
        // 对 i 结点进行下一轮调整, 其值还是 data
        start = i;
    }
    // 最后将 data 赋值给当前位置
    list.r[start] = data;
}

/**
 * 调整 以 i 结点为跟结点的子堆，
 * 递归法
 * @param i 对 i 处的元素进行调整，并递归的调整它的孩子
 */
void Sort_HeapAdjust2(SortSqList &list, int i, int n) {
    // 找出 左右孩子中 比根结点大的较大者，并与根结点交换
    int bigger = i;
    int lc = 2 * i + 1;
    int rc = 2 * i + 2;
    // 如果 左孩子较大
    if (lc < n && list.r[bigger].key < list.r[lc].key) {
        // 更新为左孩子
        bigger = lc;
    }
    // 如果 右孩子较大
    if (rc < n && list.r[bigger].key < list.r[rc].key) {
        // 更新为右孩子
        bigger = rc;
    }
    // 如果较大值 不是根结点，则需要调整
    if (bigger != i) {
        // 交换根结点与较大者
        swap(list.r[bigger], list.r[i]);
        // 递归调整交换后的子节点
        Sort_HeapAdjust2(list, n, bigger);
    }
}

/**
 * 堆排序入口
 * 堆：
 * 下标 i 的左孩子：2 * i + 1, 右孩子：2 * i + 2;
 * 下标 i 的父节点：(i - 1) / 2
 * 1. 创建大根堆
 *    从最后一个非叶子结点向前调整成堆
 *    根据完全二叉树的定义：最后一个非叶子结点的 = 最后一个结点的父节点
 *    最后一个结点 n - 1，(n - 1 - 1) / 2 = n / 2 - 1
 * 2. 逐步与根结点交换排序
 *    根据大根堆性质：根结点是整个堆里最大的。
 *    将最后一个结点与根结点交换，最大的已经到了最后，
 *    交换后调整整个堆，但是最后一个结点不再是堆的范围，
 */
void Sort_SelectionHeap(SortSqList &list) {
    // 创建大根堆 从最后一个非叶子结点向前调整成堆
    // 叶子结点不需要调整，已经满足堆的性质
    // 最后一个非叶子结点的索引是：n / 2 - 1
    for (int i = list.length / 2 - 1; i >= 0; --i) {
        Sort_HeapAdjust2(list, i, list.length);
    }
    // 根据大根堆性质，根结点肯定是整个堆里最大的。
    // 逐步将堆顶元素与堆最后一个元素交换，每交换一次，最大的值就到最后了。升序
    for (int i = list.length - 1; i > 0; --i) {
//        ElementType data = list.r[i];
//        list.r[i] = list.r[0];
//        list.r[0] = data;
        swap(list.r[0], list.r[i]);
        // 迭代调用
//        Sort_HeapAdjust(list, 0, i);
//
        // 递归调用
        Sort_HeapAdjust2(list, 0, i); // 个数在变小。后面的不需要再参与调整了
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
 * 归并排序数组迭代版本
 * @param list
 */
void Sort_MergeSortIteration(SortSqList &list) {
    // 从步长为 1 开始进行归并操作，步长逐渐加倍
    for (int size = 1; size < list.length; size *= 2) {
        for (int i = 0; i < list.length - size; i += 2 * size) {
            // [low, mid] 左半部分 包含mid
            int low = i;
            int mid = low + size - 1;
            // (mid, high] 右半部分
            int high = min(low + 2 * size - 1, list.length - 1);
            // 合并两个有序子数组
            Sort_Merge(list, low, mid, high);
        }
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
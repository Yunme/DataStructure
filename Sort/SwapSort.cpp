//
// Created by zzqni on 2024/5/1.
//

#include <random>
#include "SwapSort.h"

/**
 * 交换：冒泡排序
 */
void Sort_SwapBubble(SortSqList &list) {
    int totalCompare = 0;
    for (int i = 0; i < list.length - 1; ++i) {
        bool swapped = false;
        for (int j = 0; j < list.length - i - 1; ++j) {
            printf("元素 %d 和 元素 %d 比较\n", list.r[j].key, list.r[i].key);
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
    printf("总共比较%d次\n", totalCompare);
}


/**
 *  快排划分 普通版本
 *  划分：把比 pivot 小的元素放到它前面，大的放到后面，在一次循环中实现。
 *
 *  缺点：
 *  1. 当在顺序数组或逆序数组上时，每次拆分只少一个元素。复杂度称为 N^2，随机基准数解决
 *  2. 当数组重复元素较多时，复杂度称为 N^2，双路、三路快排解决。
 */
int Sort_SwapQuickPartitionNormal(SortSqList &list, int low, int high) {
    // 随机基准数，让正序或逆序的数组 更快。极端用例
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution dis(low, high);
    int random = dis(gen);
    swap(list.r[low], list.r[random]);

    ElementType pivot = list.r[low];
    int j = low;
    // nums[low + 1 .. j] 的元素 <= pivot
    // nums(j..i) > pivot
    for (int i = low + 1; i <= high; ++i) {
        // j 表示 <= pivot 元素中最右边元素的索引。
        // i 从 low + 1 开始，如果对应元素小于 pivot ，那么 j + 1, 就是大于 pivot 的第一个元素
        if (list.r[i].key <= pivot.key) {
            j++;
            swap(list.r[i], list.r[j]);
        }
    }
    // j 还是最右边的 <= pivot 的元素位置。
    // 最后 把 low 放到 j 的位置。
    swap(list.r[low], list.r[j]);
    return j;
}

/**
 * 交换：快速排序 分组
 * 双路快排
 */
int Sort_SwapQuickPartition(SortSqList &list, int low, int high) {
    // 随机基准数，让正序或逆序的数组 更快。极端用例
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution dis(low, high);
    int random = dis(gen);
    swap(list.r[low], list.r[random]);

    ElementType data = list.r[low];
    KeyType pivotKey = list.r[low].key;
    // 双指针一前一后
    while (low < high) {
        // high 位置 >= 基准，排序满足， high--
        // 直到 high 位置 < 基准，跳出循环，high 位置的元素存到 low 位置。
        while (low < high && list.r[high].key >= pivotKey)
            --high;
        list.r[low] = list.r[high];

        // low 位置 <= 基准，排序满足，low++
        // 直到 low 位置 > 基准，跳出循环，low 位置的元素存到 high 位置
        while (low < high && list.r[low].key <= pivotKey)
            ++low;
        list.r[high] = list.r[low];
    }
    // low 和 high 重合 位置就是基准排序位置。
    list.r[low] = data;
    return low;
}

/**
 * 交换：快速排序
 */
void Sort_SwapQuick(SortSqList &list, int low, int high) {
    if (low < high) {
//        int pivotPos = Sort_SwapQuickPartitionNormal(list, low, high);
        int pivotPos = Sort_SwapQuickPartition(list, low, high);

        Sort_SwapQuick(list, low, pivotPos - 1);
        Sort_SwapQuick(list, pivotPos + 1, high);
    }
}

/**
 * 三路快速排序
 * 解决多重复元素，递归树变长
 * 引入三段，中间段是等于 pivot 的元素
 *
 * 1. 当元素 < pivot，元素交换到 等于 pivot 区间的前一个位置
 * 2. 当元素 = pivot，什么都不做，看下一个元素
 * 3. 当元素 > pivot, 元素交换到大于 pivot 的前一个位置。
 */
void Sort_SwapQuickThreeWay(SortSqList &list, int low, int high) {
    if (low < high) {
        // 随机基准数，让正序或逆序的数组 更快。极端用例
        random_device rd;
        mt19937 gen(rd());
        uniform_int_distribution dis(low, high);
        int random = dis(gen);
        swap(list.r[low], list.r[random]);
        ElementType pivot = list.r[low];
        // 小于基准值区域的右边界
        int lessThan = low;
        // 大于基准值区域的左边界
        int greatThan = high;
        int i = low + 1;
        while (i <= greatThan) {
            if (list.r[i].key < pivot.key) {
                // 小于基准值 跟小于的右边界交换
                swap(list.r[i], list.r[lessThan]);
                lessThan++;
                i++;
            } else if (list.r[i].key > pivot.key) {
                // 大于基准值 跟大于的左边界交换
                swap(list.r[i], list.r[greatThan]);
                greatThan--;
            } else {
                // 等于基准值 不操作， i++
                i++;
            }
        }
        Sort_SwapQuickThreeWay(list, low, lessThan - 1);
        Sort_SwapQuickThreeWay(list, greatThan + 1, high);
    }
}

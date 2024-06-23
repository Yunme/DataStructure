#include "Heap.h"

#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

/**
 * 大根堆
 *
 * push() 插入一个元素，并保持堆的性质
 * pop() 删除堆顶元素，并保持堆的性质
 * erase() 删除指定 index 处元素，并保持堆的性质
 * top() 返回堆顶元素
 */

Heap::Heap() {}

Heap::Heap(vector<int> fromlist) : list(fromlist) { heapify(); }

/**
 * 插入到尾部，向上调整
 */
void Heap::push(int val) {
    list.push_back(val);
    // 向上调整
    justifyUp(list.size() - 1);
}

int Heap::top() { return list.empty() ? -1 : list[0]; }

/**
 * 堆顶移除
 * 最后一个元素移动到 0，再向下调整,
 *
 * 这样只有最后一个元素所在的分支结构变化了
 * 其他分支没变 不需要调整
 */
void Heap::pop() {
    if (!list.empty()) {
        swap(list[0], list[list.size() - 1]);
        list.pop_back();
        if (!list.empty()) {
            justifyDown(0);
        }
    }
}

/**
 * 移除某个元素
 */
void Heap::remove(int val) {
    // 先遍历查找 index
    auto pos = find(list.begin(), list.end(), val);
    if (pos == list.end()) return;
    int index = pos - list.begin();
    if (index == list.size() - 1) {
        // 删除的是最后一个 直接删除
        list.pop_back();
    } else {
        // 其他元素，与最后一个交换后调整
        int last = list.back();
        swap(list[index], list.back());
        list.pop_back();
        // 先对 index 处向下调整
        justifyDown(index);
        // 调整完后如果 index 处元素发生变化了，说明已经调整完毕。
        // 没发生变化 说明 index 向下已满足性质，需要向上检查调整
        if (list[index] == last) {
            justifyUp(index);
        }
    }
}

int Heap::size() { return list.size(); }

/**
 * 对列表 建立堆
 * 所有非叶子结点调整
 */
void Heap::heapify() {
    // 从最后一个非叶子开始调整； j 的父节点为 (j - 1) / 2
    // (list.size() - 1 - 1) / 2 = list.size() / 2 - 1
    int i = list.size() / 2 - 1;
    for (; i >= 0; i--) {
        // 每个结点向下
        justifyDown(i);
    }
}

/**
 * 向下调整 递归版本
 * 从索引 i 处的堆结点开始调整，直到结点大于两个孩子，或到叶子结点
 */
void Heap::justifyDownRecursive(int i) {
    int n = list.size();
    // 当前结点
    // 找出左右孩子中大于 i 处的较大的 和他进行交换
    int bigger = i;
    int lc = 2 * i + 1;
    int rc = 2 * i + 2;
    if (lc < n && list[lc] > list[bigger]) {
        bigger = lc;
    }
    if (rc < n && list[rc] > list[bigger]) {
        bigger = rc;
    }
    // 左右孩子中有大于根的 交换
    if (bigger != i) {
        swap(list[bigger], list[i]);
        // 递归处理交换后的
        justifyDownRecursive(bigger);
    }
}

/**
 * 向上调整 (用于在插入删除) 递归版本
 * 从索引 i 处的结点向上调整，直到当前结点小于父节点
 */
void Heap::justifyUpRecursive(int i) {
    int parent = (i - 1) / 2;
    if (parent >= 0 && list[parent] < list[i]) {
        swap(list[parent], list[i]);
        justifyUpRecursive(parent);
    }
}

/**
 * 向下调整 迭代版本
 * 从索引 i 处的堆结点开始调整，直到结点大于两个孩子，或到叶子结点
 */
void Heap::justifyDown(int i) {
    int n = list.size();
    int data = list[i];
    int half = n / 2;
    while (i < half) {
        int child = 2 * i + 1;
        int right = child + 1;
        if (right < n && list[right] > list[child]) {
            child = right;
        }
        if (list[child] <= data) break;

        list[i] = list[child];
        i = child;
    }
    list[i] = data;
}

/**
 * 向上调整 (用于在插入删除) 迭代版本
 * 从索引 i 处的结点向上调整，直到当前结点小于父节点
 */
void Heap::justifyUp(int i) {
    int data = list[i];
    while (i > 0) {
        int parent = (i - 1) / 2;
        if (list[parent] >= data) break;
        list[i] = list[parent];
        i = parent;
    }
    list[i] = data;
}

void Heap::print() {
    cout << "[";
    for (int i = 0; i < list.size(); ++i) {
        cout << list[i];
        if (i != list.size() - 1) {
            cout << ",";
        }
    }
    cout << "]" << endl;
}

// int main() {
//     vector<int> list = {2, 7, 4, 1, 8, 1};
//     Heap heap(list);
//     int top = heap.top();
//     cout << top << endl;
// }
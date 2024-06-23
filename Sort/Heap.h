#include <vector>

using namespace std;

#ifndef HEAP_H
#define HEAP_H

/**
 * 大根堆
 *
 * push() 插入一个元素，并保持堆的性质
 * pop() 删除堆顶元素，并保持堆的性质
 * erase() 删除指定 index 处元素，并保持堆的性质
 * top() 返回堆顶元素
 */
class Heap {
   public:
    Heap();
    Heap(vector<int> fromlist);
    /**
     * 插入到尾部，向上调整
     */
    void push(int val);

    int top();
    /**
     * 堆顶移除
     * 最后一个元素移动到 0，再向下调整,
     *
     * 这样只有最后一个元素所在的分支结构变化了
     * 其他分支没变 不需要调整
     */
    void pop();

    /**
     * 移除某个元素
     */
    void remove(int val);
    int size();
    void print();

   private:
    vector<int> list;
    /**
     * 对列表 建立堆
     * 所有非叶子结点调整
     */
    void heapify();
    /**
     * 向下调整
     * 从索引 i 处的堆结点开始调整，直到结点大于两个孩子，或到叶子结点
     */
    void justifyDownRecursive(int i);
    /**
     * 向上调整 (用于在插入删除)
     * 从索引 i 处的结点向上调整，直到当前结点小于父节点
     */
    void justifyUpRecursive(int i);

    /**
     * 向下调整
     * 从索引 i 处的堆结点开始调整，直到结点大于两个孩子，或到叶子结点
     */
    void justifyDown(int i);
    /**
     * 向上调整 (用于在插入删除)
     * 从索引 i 处的结点向上调整，直到当前结点小于父节点
     */
    void justifyUp(int i);
};

#endif  // HEAP_H
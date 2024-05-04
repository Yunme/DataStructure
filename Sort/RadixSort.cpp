//
// Created by zzqni on 2024/5/1.
//

#include "RadixSort.h"

/**
 * 基数排序
 */
int ord(char c) {
    //返回k的映射(个位整数)
    return c - '0';
}

void Sort_RadixDistribute(SLCell *r, int i, ArrType &f, ArrType &e) {
    for (int j = 0; j < RADIX; ++j) {
        f[j] = 0;
    }
    for (int p = r[0].next; p; p = r[p].next) {
        int j = ord(r[p].keys[i]);
        if (!f[j])
            f[j] = p;
        else
            r[e[j]].next = p;
        e[j] = p;
    }
}

int succ(int i) {
    //求后继函数
    return ++i;
}

void Sort_RadixCollect(SLCell *r, int i, ArrType &f, ArrType &e) {
    int j, t;
    for (j = 0; !f[j]; j = succ(j));            //找第一个非空子表，succ为求后继函数
    r[0].next = f[j];
    t = e[j];            //r[0].next指向第一个非空子表中第一个结点
    while (j < RADIX - 1) {
        for (j = succ(j); j < RADIX - 1 && !f[j]; j = succ(j));        //找下一个非空子表
        if (f[j]) {
            r[t].next = f[j];
            t = e[j];
        }                    //链接两个非空子表
    }//while
    r[t].next = 0;
}

void RadixSort(SLList &L) {
    //L是采用静态链表表示的顺序表
    //对L做基数排序，使得L成为按关键字自小到大的有序静态链表，L.r[0]为头结点
    int i;
    ArrType f, e;
    for (i = 0; i < L.recordNum; ++i)
        L.r[i].next = i + 1;
    L.r[L.recordNum].next = 0;                //将L改造为静态链表
    for (i = 0; i < L.keyNum; ++i) {
        //按最低位优先依次对各关键字进行分配和收集
        Sort_RadixDistribute(L.r, i, f, e);                //第i趟分配
        Sort_RadixCollect(L.r, i, f, e);                    //第i趟收集
    }
}

void RadixPrint(const SLList &L) {
    //按数组序号输出静态链表
    for (int i = 1; i <= L.recordNum; i++) {
        for (int j = L.keyNum - 1; j >= 0; j--)
            cout << L.r[i].keys[j];
        cout << endl;
    }
}

/**
 * 基数排序 使用分发收集法
 */
void RadixSort_SimpleDistribute(const vector<ElementType> &arr, vector<vector<ElementType>> &temp, int exp) {
    for (const auto &i: arr) {
        int digitNum = (i.key / exp) % 10;
        temp[digitNum].push_back(i);
    }
}

void RadixSort_SimpleCollect(vector<ElementType> &arr, vector<vector<ElementType>> &temp) {
    int k = 0;
    for (int i = 0; i < temp.size(); ++i) {
        for (int j = 0; j < temp[i].size(); ++j) {
            arr[k++] = temp[i][j];
        }
    }
    // 清空temp
    temp.clear();
    temp.resize(10);
}

void RadixSort_SimpleDistributeCollect(vector<ElementType> &arr) {
    int max = arr[0].key;
    for (int i = 1; i < arr.size(); i++) {
        if (arr[i].key > max)
            max = arr[i].key;
    }

    // 从最低位到最高位，依次进行分发收集
    vector<vector<ElementType>> temp(10);
    for (int exp = 1; max / exp > 0; exp *= 10) {
        RadixSort_SimpleDistribute(arr, temp, exp);
        RadixSort_SimpleCollect(arr, temp);
    }
}

/**
 * 基数排序 使用计数排序法
 * 对数组按照指定的位数进行排序
 */
void countSort(vector<ElementType> &arr, int exp) {
    int n = arr.size();
    vector<int> output(n, 0);
    int count[10] = {0};

    // 统计每个数字出现的次数
    for (int i = 0; i < n; i++) {
        int digitNumber = (arr[i].key / exp) % 10;
        count[digitNumber]++;
    }

    // 计算每个数字在输出数组中的位置
    for (int i = 1; i < 10; i++) {
        count[i] += count[i - 1];
    }

    // 根据计数数组将数字放入输出数组中
    for (int i = n - 1; i >= 0; i--) {
        int digitNumber = (arr[i].key / exp) % 10;
        output[count[digitNumber] - 1] = arr[i].key;
        count[digitNumber]--;
    }

    // 将排序好的数字复制回原数组
    for (int i = 0; i < n; i++) {
        arr[i] = output[i];
    }
}

void RadixSort_Count(vector<ElementType> &arr) {
    int max = arr[0].key;
    for (int i = 1; i < arr.size(); i++) {
        if (arr[i].key > max)
            max = arr[i].key;
    }

    // 从最低位到最高位，依次进行计数排序
    for (int exp = 1; max / exp > 0; exp *= 10) {
        countSort(arr, exp);
    }
}
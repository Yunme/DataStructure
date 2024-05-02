//
// Created by zzqni on 2024/4/26.
//

#include "SqSearch.h"
#include <chrono>

/**
 * 常规顺序查找
 */
int SqSearch(vector<ElementType> &array, KeyType keyType) {
    for (int i = 0; i < array.size(); ++i) {
        if (keyType == array[i].key)
            return i;
    }
    return -1;
}

void SqSearchCommon() {
    auto start = std::chrono::high_resolution_clock::now();
    int count = 1000 * 1000 * 1000;
    vector<int> array(count);
    array[1000 * 1000] = 3;
    for (int i = 0; i < count; ++i) {
        if (array[i] == 3) {
            printf("found %d\n", i);
            break;
        }
    }
    auto end = std::chrono::high_resolution_clock::now();
    // 计算执行时间
    std::chrono::duration<double> duration = end - start;
    // 输出执行时间
    std::cout << "Common Search execution time: " << duration.count() << " seconds" << std::endl;
}

/**
 * 带监视位的顺序查找
 */
void SqSearchSentinel() {
    auto start = std::chrono::high_resolution_clock::now();
    int count = 1000 * 1000 * 1000;
    vector<int> array(count);
    int key = 3;
    // 原数据位置
    array[1000 * 1000] = key;
    // 哨兵
    array[count - 1] = key;
    int i;
    for (i = 0; array[i] != key; ++i);
    printf("found %d\n", i);
    auto end = std::chrono::high_resolution_clock::now();
    // 计算执行时间
    std::chrono::duration<double> duration = end - start;
    // 输出执行时间
    std::cout << "Sentinel Search execution time: " << duration.count() << " seconds" << std::endl;
}

/**
 * 二分查找
 */
int SqSearchBinary(const vector<ElementType> &data, KeyType key) {
    int start = 0, end = data.size(), mid = (start + end) / 2;
    while (end > start) {
        if (data[mid].key == key) {
            return mid;
        }
        if (key > data[mid].key) {
            start = mid + 1;
        } else if (key < data[mid].key) {
            end = mid - 1;
        }
        mid = (start + end) / 2;
    }
    return -1;
}

/**
 * 二分查找 递归版本
 */
int SqSearchBinaryRecursive(const vector<ElementType> &data, KeyType key, int start, int end) {
    if (end <= start) return -1;
    int mid = (start + end) / 2;
    if (data[mid].key == key) return mid;
    if (key > data[mid].key)
        start = mid + 1;
    else
        end = mid - 1;
    SqSearchBinaryRecursive(data, key, start, end);
}
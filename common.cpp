//
// Created by zzqni on 2024/5/1.
//

#include "common.h"
#include "Search/SqSearch.h"
#include <random>
#include <algorithm>

/**
 * 生成若干个不重复的数字
 * @return
 */
vector<ElementType> getDataArrayForSort(int count, int max) {
    vector<ElementType> data;
    random_device rd;
    mt19937 generator(rd());
    while (data.size() < count) {
        uniform_int_distribution<int> distribution(1, max);
        int randomNumber = distribution(generator);
        ElementType e;
        e.key = randomNumber;
        e.info = "";
        if (SqSearch(data, e.key) < 0) {
            data.push_back(e);
        }
    }

    return data;
}
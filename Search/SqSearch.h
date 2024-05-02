//
// Created by zzqni on 2024/4/26.
//

#ifndef ANDROIDFRAMEWORKTEST_SQSEARCH_H
#define ANDROIDFRAMEWORKTEST_SQSEARCH_H

#include <vector>
#include "Search.h"

int SqSearch(vector<ElementType> &array, KeyType keyType);

void SqSearchCommon();

void SqSearchSentinel();

int SqSearchBinary(const vector<ElementType> &data, KeyType key);

int SqSearchBinaryRecursive(const vector<ElementType> &data, KeyType key, int start, int end);

#endif //ANDROIDFRAMEWORKTEST_SQSEARCH_H

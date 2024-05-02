//
// Created by zzqni on 2024/4/30.
//

#ifndef ANDROIDFRAMEWORKTEST_HASHTABLE_H
#define ANDROIDFRAMEWORKTEST_HASHTABLE_H

#include "search.h"

#define TABLE_SIZE 50

struct HashNode {
    ElementType data;
    HashNode *next = nullptr;
};

typedef struct Hash {
    HashNode *node = nullptr;
} HashTable[TABLE_SIZE];

void HashTable_Insert(HashTable &hashTable, const ElementType &data);

Status HashTable_Delete(HashTable &hashTable, const KeyType &key, ElementType &data);

Status HashTable_Search(const HashTable &hashTable, const KeyType &key, ElementType &data);

void HashTable_Print(const HashTable &hashTable);

#endif //ANDROIDFRAMEWORKTEST_HASHTABLE_H

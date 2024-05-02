//
// Created by zzqni on 2024/4/30.
//

#include "HashTable.h"

int HashTable_Hash(KeyType key) {
    return key % TABLE_SIZE;
}

void HashTable_Insert(HashTable &hashTable, const ElementType &data) {
    int index = HashTable_Hash(data.key);
    if (index >= 0 && index < TABLE_SIZE) {
        if (hashTable[index].node && hashTable[index].node->data.key == 0) {
            hashTable[index].node->data = data;
        } else {
            auto *node = new HashNode;
            node->data = data;
            node->next = hashTable[index].node;
            hashTable[index].node = node;
        }
    }
}

Status HashTable_Delete(HashTable &hashTable, const KeyType &key, ElementType &data) {
    int index = HashTable_Hash(key);
    if (index >= 0 && index < TABLE_SIZE) {
        HashNode *prev = nullptr;
        HashNode *node = hashTable[index].node;
        while (node) {
            if (node->data.key == key) {
                data = node->data;
                if (prev == nullptr) {
                    hashTable[index].node = node->next;
                } else {
                    prev->next = node->next;
                }
                delete node;
                return OK;
            }
            prev = node;
            node = node->next;
        }
    }
    return ERROR;
}

Status HashTable_Search(const HashTable &hashTable, const KeyType &key, ElementType &data) {
    int index = HashTable_Hash(key);
    if (index >= 0 && index < TABLE_SIZE) {
        HashNode *node = hashTable[index].node;
        while (node) {
            if (node->data.key == key) {
                data = node->data;
                return OK;
            }
            node = node->next;
        }
    }
    return ERROR;
}

void HashTable_Print(const HashTable &hashTable) {
    printf("HashTable:\n");
    for (int i = 0; i < TABLE_SIZE; ++i) {
        printf("%d:", i);
        HashNode *node = hashTable[i].node;
        while (node) {
            printf("%d", node->data.key);
            if (node->next)
                printf("->");
            node = node->next;
        }
        printf("\n");
    }
}
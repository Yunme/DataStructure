//
// Created by zzqni on 2024/4/16.
//
#ifndef ANDROIDFRAMEWORKTEST_COMMON_H
#define ANDROIDFRAMEWORKTEST_COMMON_H

#include <iostream>
#include <cstdio>
#include <vector>

using namespace std;

#define MAXSIZE 100
#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASIBLE -1
#define OVERFLOW -2

typedef int Status;
typedef char ElemType;

typedef int KeyType;
typedef string InfoType;

typedef struct ElementType {
    KeyType key;
    InfoType info;

    ElementType() = default;

    ElementType(KeyType key) {
        this->key = key;
        this->info = "";
    }
} ElementType;


vector<ElementType> getDataArrayForSort(int count = 20, int max = 100);

#endif //ANDROIDFRAMEWORKTEST_COMMON_H

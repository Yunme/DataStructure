//
// Created by zzqni on 2024/4/20.
//
#include "commonString.h"
#include <iostream>

using namespace std;

void printArray(int array[], int count) {
    cout << '[';
    for (int i = 0; i < count; ++i) {
        cout << array[i];
        if (i != count - 1)
            cout << ',';
    }
    cout << ']' << endl;
}
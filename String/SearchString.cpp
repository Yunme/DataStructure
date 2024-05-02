//
// Created by zzqni on 2024/4/19.
//

#include "SearchString.h"

void StrSearchBF1(String source, String target, int &pos) {
    int i = 0, j = 0;
    while (i < source.length && j < target.length) {
        char a = source.ch[i];
        char b = target.ch[j];
        if (a == b) {
            if (j == target.length - 1) {
                pos = i - target.length + 1;
                return;
            }
            j++;
            i++;
        } else {
            // i回到原来的位置的下一个位置
            // 因为j 从 0 开始，i-j = i移动的距离
            i = i - j + 1;
            j = 0;
        }
    }
}

bool isPrefix(const char *str1, const char *str2) {
    while (*str1 != '\0' && *str2 != '\0') {
        if (*str1 != *str2) {
            return false;
        }
        str1++;
        str2++;
    }
    return *str2 == '\0';
}

void StrSearchBF2(String source, String target, int &pos) {
    for (int i = 0; i < source.length; ++i) {
        if (isPrefix(source.ch + i, target.ch)) {
            pos = i;
            return;
        }
    }
}

void StrSearchBF3(String source, String target, int &pos) {
    // i 存储上次主串的位置
    for (int i = 0; i <= source.length - target.length; ++i) {
        int j;
        for (j = 0; j < target.length; ++j) {
            if (source.ch[i + j] != target.ch[j]) {
                break;
            }
        }
        if (j == target.length) {
            pos = i;
        }
    }
}

int StrSearchAllBF(String source, String target, int result[]) {
    int count = 0;
    int i = 0, j = 0;
    while (i < source.length && j < target.length) {
        char a = source.ch[i];
        char b = target.ch[j];
        if (a == b) {
            if (j >= target.length - 1) {
                result[count++] = i - target.length + 1;
                j = -1;
            }
            j++;
            i++;
        } else {
            // i回到原来的位置的下一个位置
            // 因为j 从 0 开始，i-j = i移动的距离
            i = i - j + 1;
            j = 0;
        }
    }
    return count;
}

/**
 * 部分匹配表 右移一位版本
 */
void getNext(char *p, int *next) {
    next[0] = -1;
    int i = 0, j = -1;
    while (i < strlen(p) - 1) {
        if (j == -1 || p[i] == p[j]) {
            i++;
            j++;
            next[i] = j;
        } else {
            j = next[j];
        }
    }
}

void StrSearchKMP(String source, String target, int &pos) {
    int next[target.length];
    getNext(target.ch, next);
    int i = 0, j = 0;
    while (i < source.length && j < target.length) {
        if (j == -1 || source.ch[i] == target.ch[j]) {
            i++;
            j++;
        } else {
            j = next[j];
        }
    }
    if (j == target.length) {
        pos = i - j;
    }
}


void getPMT(char *p, int *pmt) {
    pmt[0] = 0;
    int i = 1, j = 0;
    while (i < strlen(p)) {
        if (p[i] == p[j]) {
            pmt[i] = j + 1;
            j++;
            i++;
        } else {
            if (j == 0) {
                pmt[i] = 0;
                i++;
            } else {
                j = pmt[j - 1];
            }
        }
    }
}


void StrSearchKMP2(String source, String target, int &pos) {
    int pmt[target.length];
    getPMT(target.ch, pmt);
    int i = 0, j = 0;
    while (i < source.length && j < target.length) {
        if (source.ch[i] == target.ch[j]) {
            i++;
            j++;
        } else {
            if (j == 0)
                i++;
            else
                j = pmt[j - 1];
        }
    }
    if (j == target.length) {
        pos = i - j;
    }
}

int StrSearchAllKMP(String source, String target, int *result) {
    int pmt[target.length];
    getPMT(target.ch, pmt);
    int i = 0, j = 0;
    int count = 0;
    while (i < source.length && j < target.length) {
        if (source.ch[i] == target.ch[j]) {
            i++;
            j++;
        } else {
            if (j == 0)
                i++;
            else
                j = pmt[j - 1];
        }
        if (j == target.length) {
            result[count++] = i - j;
            j = 0;
        }
    }
    return count;
}


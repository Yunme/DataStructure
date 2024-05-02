//
// Created by zzqni on 2024/4/18.
//

#include "String.h"

// 串赋值
void StrAssign(String &s, const char *c) {
//    strcpy(s.ch, c);
//    s.length = strlen(c);
    s.length = 0;
    while (*c != '\0') {
        s.ch[s.length++] = *c;
        c++;
    }
    s.ch[s.length] = '\0';
}

void StrPrint(String s) {
    for (int i = 0; i < s.length; ++i) {
        cout << s.ch[i];
    }
    cout << endl;
}

// 串比较 0, s<t:-1, s>t:1
int StrCompare(String s, String t) {
    if (s.length < t.length) return -1;
    else if (s.length > t.length) return 1;
    else {
        for (int i = 0; i < s.length; ++i) {
            if (s.ch[i] < t.ch[i])
                return -1;
            else if (s.ch[i] > t.ch[i])
                return 1;
        }
        return 0;
    }
}

int StrCompare1(String s, String t) {
    int i;
    for (i = 0; s.ch[i] != '\0' && t.ch[i] != '\0'; i++) {
        if (s.ch[i] != t.ch[i])
            return s.ch[i] < t.ch[i] ? -1 : 1;
    }
    if (s.ch[i] == '\0' && t.ch[i] == '\0')
        return 0; // 完全相等
    else
        return s.ch[i] == '\0' ? -1 : 1; // 短的较小
}

int StrCompare2(String s, String t) {
    char *str1 = s.ch;
    char *str2 = t.ch;
    while (*str1 && *str2) {
        if (*str1 < *str2) {
            return -1; // str1 小于 str2
        } else if (*str1 > *str2) {
            return 1; // str1 大于 str2
        }
        str1++;
        str2++;
    }

    if (*str1 == '\0') {
        if (*str2 == '\0') {
            return 0; // str1 等于 str2
        } else {
            return -1; // str1 小于 str2
        }
    } else {
        return 1; // str1 大于 str2
    }
}

// 串长度
int StrLength(String s) {
    return s.length;
}

// 相连
int StrConcat(String &t, String s1, String s2) {
    StrAssign(t, s1.ch);
    char *a = s2.ch;
    while (*a != '\0') {
        t.ch[t.length++] = *a;
        a++;
    }
    t.ch[t.length] = '\0';
    return 0;
}

// 求子串 存到sub里
void StrSubString(String &sub, String s, int pos, int len) {
    if (pos > s.length - 1 || pos < 0 || len <= 0 || pos + len > s.length) {
        return;
    }
    sub.length = 0;
    for (int i = 0; i < len; ++i) {
        sub.ch[i] = s.ch[pos + i];
        sub.length++;
    }
    sub.ch[sub.length] = '\0';
}

// 串拷贝
void StrCopy(String &t, String s) {
    StrAssign(t, s.ch);
}

// 串判空
bool StrEmpty(String s) {
    return s.length == 0;
}

// 清空串
void StrClear(String &s) {
    for (int i = 0; i < s.length; ++i) {
        s.ch[i] = '\0';
    }
}

// 子串替换
void StrReplaceFirst(String &s, String a, String replacement) {
    int pos = -1;
    StrIndexFirst(s, a, pos);
    if (pos >= 0) {
        StrDelete(s, pos, a.length);
        StrInsert(s, pos, replacement);
    }
}

void StrReplaceAll(String &s, String target, String replacement) {
    int result[s.length];
    int count = StrIndex(s, target, result);
    int offset = 0;
    for (int i = 0; i < count; ++i) {
        int pos = result[i];
        if (i != 0) {
            offset += replacement.length - target.length;
            pos += offset;
        }
        StrDelete(s, pos, target.length);
        StrInsert(s, pos, replacement);
    }
}

// 子串插入
void StrInsert(String &s, int pos, String t) {
    if (pos < 0 || pos > s.length) return;
    for (int i = s.length - 1; i >= pos; i--) {
        s.ch[i + t.length] = s.ch[i];
    }
    for (int i = 0; i < t.length; ++i) {
        s.ch[pos + i] = t.ch[i];
    }

    s.length += t.length;
    s.ch[s.length] = '\0';
}

// 子串销毁
void StrDelete(String &s, int pos, int len) {
    if (pos < 0 || pos > s.length) return;
    len = pos + len > s.length ? s.length - pos : len;
    int i = pos + len;
    while (i < s.length) {
        s.ch[pos++] = s.ch[i++];
    }
    s.length -= len;
    s.ch[s.length] = '\0';
}

// 销毁
void StrDestroy(String &s) {
    StrClear(s);
}

// 寻找匹配的第一个子串的位置
// BF 暴力查找 O(m*n)
void StrIndexFirst(String source, String target, int &pos) {
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
            i = i - j + 1;
            j = 0;
        }
    }
}

int StrIndex(String source, String target, int result[]) {
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
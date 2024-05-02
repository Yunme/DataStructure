//
// Created by zzqni on 2024/4/18.
//

#ifndef ANDROIDFRAMEWORKTEST_STRING_H
#define ANDROIDFRAMEWORKTEST_STRING_H

#include <cstdio>
#include <cstring>
#include <iostream>
#include "../common.h"
#include "commonString.h"

using namespace std;

typedef struct {
    char ch[MAXLENGTH + 1];
    int length;
} String;

void StrPrint(String s);

void StrAssign(String &s, const char *c);

int StrCompare(String s, String t);

int StrCompare1(String s, String t);

int StrCompare2(String s, String t);

int StrLength(String s);

int StrConcat(String &t, String s1, String s2);

void StrSubString(String &sub, String s, int pos, int len);

void StrCopy(String &t, String s);

bool StrEmpty(String s);

void StrClear(String &s);

void StrReplaceFirst(String &s, String a, String replacement);

void StrReplaceAll(String &s, String target, String replacement);

void StrInsert(String &s, int pos, String t);

void StrDelete(String &s, int pos, int len);

void StrDestroy(String &s);

void StrIndexFirst(String source, String target, int &pos);

int StrIndex(String source, String target, int result[]);

#endif //ANDROIDFRAMEWORKTEST_STRING_H

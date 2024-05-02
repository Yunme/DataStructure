//
// Created by zzqni on 2024/4/19.
//

#include "testString.h"
#include <cassert>
#include <fstream>
#include <random>
#include <ctime>



void testCommonString() {
    String s1, s2;
    StrAssign(s1, "acdef");
    StrAssign(s2, "bcde");
    StrPrint(s1);
    StrPrint(s2);
    int compare = StrCompare2(s1, s2);
    printf("compare: %s with %s : %d\n", s1, s2, compare);
    int length1 = StrLength(s1);
    int length2 = StrLength(s2);
    printf("length: %s: %d, %s: %d\n", s1, length1, s2, length2);
    String s3;
    StrConcat(s3, s1, s2);
    printf("concat %s,%s=%s, length=%d\n", s1, s2, s3, StrLength(s3));
    String s4;
    StrSubString(s4, s3, 3, 2);
    printf("substring %s: index=%d,len=%d->%s\n", s3, 3, 2, s4);
    String s5;
    StrCopy(s5, s4);
    StrPrint(s5);
    printf("insert %s: index=%d with %s ->", s1, 2, s4);
    StrInsert(s1, 4, s4);
    printf("%s\n", s1);
    int index = 1, len = 0;
    printf("delete %s: index=%d,len=%d->", s1, index, len);
    StrDelete(s1, index, len);
    printf("%s\n", s1);
    StrAssign(s1, "aaaaaabaaaaaabaaaaaabaaaaaab");
    StrAssign(s2, "aaab");
    int pos = -1;
    StrIndexFirst(s1, s2, pos);
    printf("index of %s from %s:index=%d\n", s2, s1, pos);
    int result[s1.length];
    int count = StrIndex(s1, s2, result);
    printArray(result, count);

    StrAssign(s3, "a");
    StrAssign(s4, "");
//    printf("replace first %s with %s in %s:", s3, s4, s1);
//    StrReplaceFirst(s1, s3, s4);
//    printf("%s\n", s1);
    printf("replace all %s with %s in %s:", s3, s4, s1);
    StrReplaceAll(s1, s3, s4);
    printf("%s\n", s1);
}

void testString() {
//   testCommonString();
//    testSearchString();
//    testCommonString()
    testSearchFile();
}

void testSearchString() {
    char *c = "ABCDAB";
    int next[strlen(c)];
    getNext("ABCDAB", next);
    printArray(next, strlen(c));

    String search, s1, s2, s3;
    StrAssign(search, "aaab");
    StrAssign(s1, "aaaaab");
    int pos = -1;
    StrSearchBF1(s1, search, pos);
    assert(pos == 2);

    StrSearchBF2(s1, search, pos);
    assert(pos == 2);

    StrSearchBF3(s1, search, pos);
    assert(pos == 2);

    StrSearchKMP(s1, search, pos);
    assert(pos == 2);

    StrSearchKMP2(s1, search, pos);
    assert(pos == 2);

    StrAssign(search, "aaab");
    StrAssign(s1, "aaaaabaaaaabaaaaab");
    int result[100];
    printf("index of %s from %s:index=", search, s1);
    int count = StrSearchAllKMP(s1, search, result);
    printArray(result, count);
}


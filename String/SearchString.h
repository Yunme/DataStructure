//
// Created by zzqni on 2024/4/19.
// 字符串子串查找
//

#ifndef ANDROIDFRAMEWORKTEST_SEARCHSTRING_H
#define ANDROIDFRAMEWORKTEST_SEARCHSTRING_H

#include "String.h"

/**
 * 暴力查找
 */
void StrSearchBF1(String source, String target, int &pos);

void StrSearchBF2(String source, String target, int &pos);

void StrSearchBF3(String source, String target, int &pos);

int StrSearchAllBF(String source, String target, int result[]);

void getNext(char *p, int *next);

void StrSearchKMP(String source, String target, int &pos);


void getPMT(char *p, int *pmt);

void StrSearchKMP2(String source, String target, int &pos);


int StrSearchAllKMP(String source, String target, int *result);

#endif //ANDROIDFRAMEWORKTEST_SEARCHSTRING_H

//
// Created by zzqni on 2024/4/20.
//

#ifndef ANDROIDFRAMEWORKTEST_SEARCHFILE_H
#define ANDROIDFRAMEWORKTEST_SEARCHFILE_H

#include <vector>
#include "SearchString.h"

void testSearchFile();

void readAndSearch();

void readFile(char *&array);

void writeFile();

void searchByBF(String source, String search);

void searchByKMP(String source, String search);


#endif //ANDROIDFRAMEWORKTEST_SEARCHFILE_H

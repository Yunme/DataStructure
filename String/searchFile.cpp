//
// Created by zzqni on 2024/4/20.
//

#include "searchFile.h"
#include <iostream>
#include <fstream>
#include <random>
#include <ctime>
#include <chrono>

void testSearchFile() {
//    writeFile();
    readAndSearch();
}

void readAndSearch() {
    char *array;
    readFile(array);
    String source;
    String search;
    StrAssign(source, array);
    StrAssign(search, "aab");

    searchByBF(source, search);
//    searchByKMP(source, search);
}

void searchByBF(String source, String search) {
    // 获取当前时间点
    auto start = std::chrono::high_resolution_clock::now();
    // 执行要测量时间的方法
    int result[1000];
    int count = StrSearchAllBF(source, search, result);
    printf("found: %d\n", count);
    printArray(result, count);
    // 获取当前时间点
    auto end = std::chrono::high_resolution_clock::now();
    // 计算执行时间
    std::chrono::duration<double> duration = end - start;
    // 输出执行时间
    std::cout << "BF execution time: " << duration.count() << " seconds" << std::endl;
}

void searchByKMP(String source, String search) {
    // 获取当前时间点
    auto start = std::chrono::high_resolution_clock::now();
    // 执行要测量时间的方法
    int result[1000];
    int count = StrSearchAllKMP(source, search, result);
    printf("found: %d\n", count);
    printArray(result, count);
    // 获取当前时间点
    auto end = std::chrono::high_resolution_clock::now();
    // 计算执行时间
    std::chrono::duration<double> duration = end - start;
    // 输出执行时间
    std::cout << "KMP execution time: " << duration.count() << " seconds" << std::endl;
}

void readFile(char *&array) {
    std::ifstream file("../random_chars.txt"); // 打开文件 example.txt，注意文件路径需要根据实际情况修改

    if (!file.is_open()) {
        std::cerr << "Failed to open the file." << std::endl;
    }

    file.seekg(0, std::ios::end); // 将文件指针移动到文件末尾
    std::streampos fileSize = file.tellg(); // 获取当前文件指针位置，即文件大小
    file.seekg(0, std::ios::beg); // 将文件指针移动回文件开头

    // 动态分配字符数组并读取文件内容
    array = new char[fileSize]; // 创建一个大小为文件大小的字符数组
    file.read(array, fileSize); // 从文件中读取内容到字符数组
    file.close(); // 关闭文件
}

void writeFile() {
    std::ofstream outfile("../random_chars.txt"); // 打开文件 random_chars.txt，如果不存在则创建新文件

    if (!outfile.is_open()) {
        std::cerr << "Failed to create/open the file." << std::endl;
    }

    // 设置随机数生成器
    std::mt19937 rng(std::time(nullptr)); // 使用当前时间作为随机数种子
    std::uniform_int_distribution<char> dist('a', 'z'); // 生成范围在'A'到'Z'之间的字符

    const int num_chars = MAXLENGTH - 1024; // 要生成的字符数量

    // 生成随机字符并写入文件
    for (int i = 0; i < num_chars; ++i) {
        char random_char = dist(rng); // 生成一个随机字符
        outfile << random_char; // 将随机字符写入文件
    }

    outfile.close(); // 关闭文件

    std::cout << "Random characters generated and saved to random_chars.txt." << std::endl;
}


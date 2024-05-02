//
// Created by zzqni on 2024/4/20.
//

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <random>
#include <chrono>

using namespace std;

// Generate a random text file
void generateRandomTextFile(const string& filename, int length) {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<int> dis('a', 'z');

    ofstream file(filename);
    for (int i = 0; i < length; i++) {
        file << (char)dis(gen);
    }
    file.close();
}

// Read the contents of a text file
string readFile(const string& filename) {
    ifstream file(filename);
    string text;
    getline(file, text, '\0');
    file.close();
    return text;
}

// Implement the BF algorithm
int bfMatch(const string& text, const string& pattern) {
    int n = text.length();
    int m = pattern.length();
    for (int i = 0; i <= n - m; i++) {
        bool match = true;
        for (int j = 0; j < m; j++) {
            if (text[i + j] != pattern[j]) {
                match = false;
                break;
            }
        }
        if (match) {
            return i;
        }
    }
    return -1;
}

// Implement the KMP algorithm
int kmpMatch(const string& text, const string& pattern) {
    int n = text.length();
    int m = pattern.length();

    vector<int> next(m);
    next[0] = 0;
    for (int i = 1; i < m; i++) {
        int j = next[i - 1];
        while (j > 0 && pattern[i] != pattern[j]) {
            j = next[j - 1];
        }
        next[i] = j + 1;
    }

    int i = 0;
    int j = 0;
    while (i < n && j < m) {
        if (text[i] == pattern[j]) {
            i++;
            j++;
        } else {
            if (j == 0) {
                i++;
            } else {
                j = next[j - 1];
            }
        }
    }

    if (j == m) {
        return i - j;
    } else {
        return -1;
    }
}

 void testSearchFileMain() {
    // Generate a random text file
    string filename = "random_text.txt";
    int textLength = 1024 * 1024 * 100; // 1 million characters
    generateRandomTextFile(filename, textLength);

    // Read the text from the file
    string text = readFile(filename);

    // Pattern to be searched
    string pattern = "abcabcabc";

    // Time the BF algorithm
    auto start = chrono::high_resolution_clock::now();
    int bfIndex = bfMatch(text, pattern);
    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double> bfTime = end - start;

    cout << "BF algorithm: " << bfTime.count() << " seconds" << endl;

    // Time the KMP algorithm
    start = chrono::high_resolution_clock::now();
    int kmpIndex = kmpMatch(text, pattern);
    end = chrono::high_resolution_clock::now();
    chrono::duration<double> kmpTime = end - start;

    cout << "KMP algorithm: " << kmpTime.count() << " seconds" << endl;

    // Check if the patterns were found at the same index
    if (bfIndex == kmpIndex) {
        cout << "Pattern found at index: " << bfIndex << endl;
    } else {
        cout << "Error: Pattern found at different indices" << endl;
    }
}
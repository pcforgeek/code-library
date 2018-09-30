#include <vector>
#include <iostream>
#include <cstring>
#include "dynamic_programming_driver.h"
#include "dynamic_programming.h"

using std::vector;

// It is used to identify how much less call were required by us when we are using memoization
int count = 0;
const int DEFAULT_VALUE = 0;

// the firstSize and secondSize represent _size not the index
int longestCommonSubsequence(const char *first, const char *second, int firstSize, int secondSize) {
    count++;
    if (firstSize == 0 || secondSize == 0) {
        // if any of the string is finished then there is nothing left to compared with other string
        return 0;
    } else if (first[firstSize - 1] == second[secondSize - 1]) {
        // check if last index is same then we have 1 more common character in string
        // and add it with the count of character given by rest of characters of both string
        return 1 + longestCommonSubsequence(first, second, firstSize - 1, secondSize - 1);
    } else {
        // if both not same keep the current count as the max of
        // - if the second last character of second string match with last char of first string
        // - if the second last character of first string match with last char of secong string
        return std::max(longestCommonSubsequence(first, second, firstSize, secondSize - 1),
                        longestCommonSubsequence(first, second, firstSize - 1, secondSize));
    }
}

int longestCommonSubsequenceMemo(const char *first, const char *second, int firstSize, int secondSize,
                                 vector<vector<int> > &mem) {
    count++;
    if (firstSize == 0 || secondSize == 0) {
        // if any of the string is finished then there is nothing left to compared with other string
        return 0;
    } else {
        if (mem[firstSize - 1][secondSize - 1] != DEFAULT_VALUE)
            return mem[firstSize - 1][secondSize - 1];
    }
    if (first[firstSize - 1] == second[secondSize - 1]) {
        // check if last index is same then we have 1 more common character in string
        // and add it with the count of character given by rest of characters of both string
        mem[firstSize - 1][secondSize - 1] =
                1 + longestCommonSubsequenceMemo(first, second, firstSize - 1, secondSize - 1, mem);
        return mem[firstSize - 1][secondSize - 1];
    } else {
        // if both not same keep the current count as the max of
        // - if the second last character of second string match with last char of first string
        // - if the second last character of first string match with last char of secong string
        mem[firstSize - 1][secondSize - 1] = std::max(
                longestCommonSubsequenceMemo(first, second, firstSize, secondSize - 1, mem),
                longestCommonSubsequenceMemo(first, second, firstSize - 1, secondSize, mem));
        return mem[firstSize - 1][secondSize - 1];
    }
}

void printLongestCommomSubsequence(vector<vector<int>> &A, int rowSize, int colSize, int pathSize, const char *first,
                                   const char *second) {
    char path[pathSize + 1];
    path[pathSize] = '\0';

    // how rowSize and rowSize-1 made difference?
    int i = rowSize - 1, j = colSize - 1;
    while (i > 0 && j > 0) {
        // If current character in X[] and Y are same, then
        // current character is part of LCS
        if (first[i - 1] == second[j - 1]) {
            path[pathSize - 1] = first[i - 1]; // Put current character in result
            i--;
            j--;
            pathSize--;     // reduce values of i, j and index
        }

            // If not same, then find the larger of two and
            // go in the direction of larger value
        else if (A[i - 1][j] > A[i][j - 1])
            i--;
        else
            j--;
    }

    std::cout << path << std::endl;
}

int longestCommonSubsequenceIterative(const char *first, const char *second, int firstSize, int secondSize) {
    // TODO is it possible to write this program with storage of firstSize * secondSize only
    vector<vector<int> > mem(firstSize + 1, std::vector<int>(secondSize + 1, DEFAULT_VALUE));

    // bottom up fashion
    for (int i = 0; i <= firstSize; ++i) {
        for (int j = 0; j <= secondSize; ++j) {
            if (i == 0 || j == 0) {
                mem[i][j] = 0;
            } else if (first[i - 1] == second[j - 1]) {
                // should not be valid for 0th row and 0th col
                // which is handled in first if statement
                mem[i][j] = 1 + mem[i - 1][j - 1];
            } else {
                mem[i][j] = std::max(mem[i][j - 1], mem[i - 1][j]);
            }
        }
    }
    printLongestCommomSubsequence(mem, firstSize + 1, secondSize + 1, mem[firstSize][secondSize], first, second);
    return mem[firstSize][secondSize];
}

void longestCommonSubsequenceDriver() {
    char first[] = "AGGTAB";
    char second[] = "GXTXAYB";
    int firstSize = strlen(first);
    int secondSize = strlen(second);
    // correct ans is 4
    //std::cout << longestCommonSubsequence(first, second, firstSize, secondSize) << std::endl;
    //std::cout << count;

    // vector<vector<int> > mem(1, std::vector<int>(1, DEFAULT_VALUE)); - will only initialize with 1 row and 1 column
    // with DEFAULT_VALUE so when we try to access more than that that get SIGSEGV as even though vector allow dynamic
    // allocation we are accessing it before allocating so causing this error
    //vector<vector<int> > mem(firstSize, std::vector<int>(secondSize, DEFAULT_VALUE));
    //std::cout << longestCommonSubsequenceMemo(first, second, firstSize, secondSize, mem) << std::endl;
    //std::cout << count;

    /* Storage of memoized program
        0 0 0 0 1 1 0
        1 1 1 1 1 1 0
        1 1 1 1 1 1 0
        0 0 2 2 2 2 0
        0 0 0 0 3 3 0
        0 0 0 0 0 0 4
     */

    std::cout << longestCommonSubsequenceIterative(first, second, firstSize, secondSize) << std::endl;

    /* Storage of iterative
        0 0 0 0 0 0 0 0
        0 0 0 0 0 1 1 1
        0 1 1 1 1 1 1 1
        0 1 1 1 1 1 1 1
        0 1 1 2 2 2 2 2
        0 1 1 2 2 3 3 3
        0 1 1 2 2 3 3 4
     */

}

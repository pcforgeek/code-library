#include <string>
#include <complex>
#include <iostream>

using std::string;
/**
 * Rabin Karp pattern matching algorithm
 * Best case O(n+p)
 * Worst case O(np)
 */

int prime = 101; // any prime number - to generate hash

long createHash(string text, unsigned long end) {
    long hash = 0;
    // for createHash the starting index is always 0;
    for (unsigned int i = 0; i < end; ++i) {
        hash += (long) (text[i] * std::pow(prime, i));
    }
    return hash;
}

long createRollingHash(string text, long oldHash, unsigned long replacingIdx, unsigned long newIdx) {
    long newHash = oldHash - text[replacingIdx];
    newHash = newHash / prime;
    newHash += (long) (text[newIdx] * std::pow(prime, newIdx - replacingIdx - 1));
    return newHash;
}

bool checkEqual(string str1, int startIdx1, int endIdx1, string str2, int startIdx2, int endIdx2) {
    if (endIdx1 - startIdx1 != endIdx2 - startIdx2) {
        return false;
    }

    while (startIdx1 <= endIdx1 && startIdx2 <= endIdx2) {
        if (str1[startIdx1] != str2[startIdx2]) {
            return false;
        }
        ++startIdx1;
        ++startIdx2;
    }
    return true;
}

// return index where pattern start
long rabinKarp(const string &text, const string &pattern) {
    long patternHash = createHash(pattern, pattern.length());
    long textHash = createHash(text, pattern.length());
    for (unsigned long i = 0; i <= (text.length() - pattern.length()); ++i) {
        if (patternHash == textHash) {
            if (checkEqual(text, i, i + pattern.length() - 1, pattern, 0, pattern.length() - 1)) {
                return i;
            }
        } else {
            textHash = createRollingHash(text, textHash, i, i + pattern.length());
        }
    }
    return -1;
}

void rabinKarpDriver() {
    std::cout << rabinKarp("some text", "ext") << std::endl;
    std::cout << rabinKarp("hello world", "hell") << std::endl;
    std::cout << rabinKarp("Joely", "e") << std::endl;
}
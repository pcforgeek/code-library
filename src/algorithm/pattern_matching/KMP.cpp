#include <vector>
#include <string>
#include <algorithm>
#include <iostream>

using std::vector;
using std::string;
/**
 * Knuth-Morris-Pratt Pattern Matching
 * O(n+p) and space S(p) where 'p' is pattern length
 **/
// O(p) and S(p)
vector<int> computePrefixSuffixArray(string pattern) {
    // every element of array will contain the (index of next element to be matched)/(length) of suffix
    // which match prefix of the partial pattern string from index 0 to some 'k' 0 <= k < p
    vector<int> prefixArray(pattern.length(), -1);
    //suffixIdx - tell us about the length of longest suffix, i.e idx where suffix end
    int pIdx = 1, suffixIdx = 0;
    prefixArray[0] = 0;
    while (pIdx < pattern.length()) {
        if (pattern[pIdx] == pattern[suffixIdx]) {
            // why we assign suffixIdx + 1?
            // to store position of suffix end or index of next element to be matched
            prefixArray[pIdx] = suffixIdx + 1;
            ++suffixIdx;
            ++pIdx;
        } else {
            if (suffixIdx != 0) {
                // why not suffixIdx = prefixArray[suffixIdx]
                // as ++suffixIdx is done in (pattern[pIdx] == pattern[suffixIdx]) if block
                // is the 'index' update for next iteration
                suffixIdx = prefixArray[suffixIdx - 1];
                // why don't we update pIdx here, see reason to why didn't we update 'i' index? in kmp method
            } else {
                prefixArray[pIdx] = 0;
                ++pIdx;
            }
        }
    }
    return prefixArray;
}

bool KMP(string text, string pattern) {
    vector<int> preComp = computePrefixSuffixArray(pattern);
    int i = 0, pIdx = 0;
    // as pIdx < pattern.length() loop will end after finding first occurrence
    while (i < text.length() && pIdx < pattern.length()) {
        if (text[i] == pattern[pIdx]) {
            ++pIdx;
            ++i;
        } else {
            if (pIdx != 0) {
                // deciding where start matching the 'pattern' from, after the mismatch
                pIdx = preComp[pIdx - 1];
                // why didn't we update 'i' index?
                // because this index (i.e 'i') was not solved as text[i] == pattern[pIdx] was not true
                // pIdx - It is the index of next character of 'pattern' to be matched with the
                // current index 'i' of 'text' as for this 'i' text[i] != pattern[pIdx]
                // (both 'pattern' and 'text' index's value didn't match), so we don't increment 'i'
                // incrementing 'i' means we have solved the text till ith index
                // i.e no pattern was found till this position in 'text'
            } else {
                // we start from next index of 'text' string when, there is no suffix which is a prefix
                // for the partial 'pattern' string match we got
                // when pIdx == 0 it means there is not suffix which is not prefix
                ++i;
            }
        }
    }
    // complete pattern has been matched successfully,
    // i.e when we have matched the last index of 'pattern'
    return pIdx == pattern.length();
}

void kmpDriver() {
    string str = "abcxabcdabcdabcy";
    string subString = "abcdabcy";
    std::cout << KMP(str, subString); //1
}

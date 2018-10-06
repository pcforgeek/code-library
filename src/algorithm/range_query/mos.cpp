#include <algorithm>
#include <iostream>
#include <complex>
#include "algorithm_driver.h"
#include "algorithms.h"

/**
 * Query Square Root Decomposition
 * Even though it is Square Root Decomposition it does not have any storage of square root size.
 * It only divide the queries into blocks (which are based on size of array).
 * It is not necessary that every block will have query.
 * It is used when we have  a static list of queries
 * It does not support update
 * Pre processing take O(nlogn) time
 */

class Query {
public:
    int idx;
    int left;
    int right;

    Query(int idx, int left, int right) {
        this->idx = idx;
        this->left = left;
        this->right = right;
    }
};

int block;

bool compare(Query x, Query y) {
    if (x.left / block != y.left / block) {
        // comparing when both x and y are in different block
        // how to decide when to use < or >
        return x.left / block < y.left / block;
    }

    // how to compare when both are in same block
    // using the right or high value of range
    return x.right < y.right;
}

int *mos(const int *arr, Query *queries, int arrlen, int querylen) {
    int *sum = new int[querylen];
    block = static_cast<int>(std::sqrt(arrlen));

    // void sort(T first, T last, Compare comp);
    std::sort(queries, queries + querylen, compare);

    // what was wrong with currR = 0;
    int currL = 0, currR = -1;
    int currSum = 0;

    for (int i = 0; i < querylen; ++i) {
        Query query = queries[i];
        int left = query.left;
        int right = query.right;

        // this will end only after accounting currL = left only
        while (currL > left) {
            // -- first as we have already accounted it in currSum
            currL--;
            currSum += arr[currL];
        }

        // this will end only after accounting currL = left only
        while (currL < left) {
            // subtract value at currL first as we have already accounted it in currSum
            currSum -= arr[currL];
            currL++;

        }

        while (currR > right) {
            currSum -= arr[currR];
            currR--;
        }

        // will end after accounting for currR == right
        while (currR < right) {
            currR++;
            currSum += arr[currR];
        }

        // for current query we keeping sum here
        sum[query.idx] = currSum;
    }

    return sum;
}

void mosDriver() {
    int a[] = {1, 1, 2, 1, 3, 4, 5, 2, 8};
    int arrlen = sizeof(a) / sizeof(a[0]);
    Query queries[] = {{0, 0, 4},
                       {1, 1, 3},
                       {2, 2, 4}};
    int querylen = sizeof(queries) / sizeof(queries[0]);
    std::cout << "Running queries \n";
    int *ans = mos(a, queries, arrlen, querylen);
    for (int i = 0; i < querylen; ++i) {
        std::cout << ans[i] << "\n";
    }
}
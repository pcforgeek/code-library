#include <cmath>
#include <vector>
#include <iostream>
#include "algorithm_driver.h"
#include "algorithms.h"

using std::vector;

class SparseTable {
private:
    int *arr;
    unsigned int row;
    vector<vector<int>> lookup;
public:
    SparseTable(int *arr, unsigned int row) {
        this->arr = arr;
        this->row = row;

        int log1 = getLog(row);
        lookup = vector<vector<int>>(row, vector<int>(log1 + 1));

        for (int k = 0; k < row; ++k) {
            lookup[k][0] = k;
        }

        for (int i = 1; i <= log1; ++i) {
            for (int j = 0; j + ((1 << i) - 1) < row; ++j) {
                // we are filling by column
                // here i-1 or log-1 as we are looking at previous level/ column
                lookup[j][i] = arr[lookup[j][i - 1]] > arr[lookup[j + (1 << (i - 1))][i - 1]] ?
                               lookup[j + (1 << (i - 1))][i - 1] :
                               lookup[j][i - 1];
            }
        }
    }

    /**
     * @param low - lower index of range
     * @param max - upper limit of range
     * @return
     */
    int query(int low, int max) {
        int logMax = getLog(max - low + 1);
        return std::min(arr[lookup[low][logMax]], arr[lookup[max - (1 << (logMax)) + 1][logMax]]);
    }

    int getLog(int n) {
        int log = 0;
        while ((1 << log) < n) {
            log++;
        }
        if ((1 << log) > n) {
            log--;
        }
        return log;
    }
};


void sparseTableDriver() {
    int arr[12] = {1, -4, 6, 3, 9, 0, 3, -1, 9, 3, 2, -5};
    auto *sparseTable = new SparseTable(arr, 12);
    std::cout << arr[sparseTable->query(0, 11)] << std::endl;// -4
    std::cout << sparseTable->query(3, 11) << std::endl;// -1
}
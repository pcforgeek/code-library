#include "algorithms.h"
#include <utility>
#include "algorithm_driver.h"
#include <complex>
#include <vector>
#include <iostream>

using std::vector;

class SquareRootDecomposition {
private:
    vector<int> arr;
    vector<int> sqrt;
    unsigned int blockSize;
public:
    SquareRootDecomposition(vector<int> arr) {
        this->arr = std::move(arr);
        blockSize = static_cast<unsigned int>(std::sqrt(this->arr.size()));
        sqrt = vector<int>(blockSize);
        for (int i = 0; i < this->arr.size(); ++i) {
            sqrt[i / blockSize] += this->arr[i];
        }
    }

    /**
     * @param low - range's starting index
     * @param high - ending index (inclusive)
     * @return
     */
    int query(int low, int high) {
        int rv = 0;

        for (int i = low; i < (((low / blockSize) + 1) * blockSize); ++i) {
            rv += arr[i];
        }

        // here each step contain sum of element of that block
        for (int j = low / blockSize + 1; j < high / blockSize; ++j) {
            rv += sqrt[j];
        }

        for (int k = (high / blockSize) * blockSize; k <= high; ++k) {
            rv += arr[k];
        }

        return rv;
    }

    void update(int value, int index) {
        // arr[index] - value -> will this be wrong??
        // value - arr[index] signify how much change happened
        sqrt[index / blockSize] = value - arr[index];
        arr[index] = value;
    }
};

void squareRootDecompositionDriver() {
    vector<int> arr = {1, 4, 2, 9, -1, 5, 0, 18, 7, 6};

    SquareRootDecomposition *obj = new SquareRootDecomposition(arr);
    int q, l, r, val, idx;
    std::cin >> q;
    for (int i = 0; i < q; i++) {
        int type;
        std::cin >> type;

        if (type == 0) {
            std::cin >> l >> r;
            std::cout << obj->query(l, r) << std::endl;
        } else {
            std::cin >> val >> idx;
            obj->update(val, idx);
        }
    }
}

// test cases
/*
5
0 1 5
0 2 7
0 5 9
1 10 5
0 5 9
*/
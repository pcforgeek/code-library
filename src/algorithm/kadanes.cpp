
#include <vector>
#include <climits>
#include <cstdio>

using std::vector;

// for finding largest sum continuous sub array
// Is there any optimal substructure property to label its as dynamic programming?
vector<int> kadance(vector<int> arr) {

    // currMax is initially set to 0 as it is the identity of sum and we are add the values of array to it
    long currMax = 0;
    long overallMax = INT_MIN;
    int start = 0, end = 0;
    int temp_start = 0;
    for (int i = 0; i < arr.size(); ++i) {
        currMax += arr[i];
        if (currMax > overallMax) {
            overallMax = currMax;
            start = temp_start;
            end = i;
        }

        // this will come after checking the currMax > overallMax as we are required
        // otherwise it will fail for test case where all are negative
        // when all are negative we will get only one element as
        // - adding of two negative number will always result in smaller number
        // - there is no chance that the value will grow
        // - value will only grow when
        if (currMax < 0) {
            // Why is currMax set to 0 here why not INT_MIN? - even though we set it to 0 but before comparison with overallMax
            // we would have added the array element to it so it is same as comparing the single element with overallMax
            // Why did I think that currMax should not be 0 - trouble understanding for array with all negative element
            currMax = 0;
            temp_start = i + 1;
        }
    }

    vector<int> subarray;
    for (int j = start; j <= end; ++j) {
        subarray.push_back(arr[j]);
    }
    // the largest sum continuous subarray
    return subarray;
}

int kadanesDriver() {
    vector<int> arr = {-2, -3, -4, -1, -2, -1, -5, -3};
    vector<int> result = kadance(arr);
    for (int i : result) {
        printf("%i ", i);
    }
}
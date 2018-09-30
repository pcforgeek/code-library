#include <iostream>
#include "algorithm_driver.h"
#include "algorithms.h"

void swap(int *a, int *b) {
    int temp = *b;
    *b = *a;
    *a = temp;
}

int partition(int arr[], int low, int high) {
    int length = high - low;
    int pivot = arr[low + length];
    int partitionIndex = low - 1;
    for (int i = low; i <= (low + length) - 1; ++i) {
        if (arr[i] <= pivot) {
            partitionIndex++;
            swap(&arr[partitionIndex], &arr[i]);
        }
    }
    swap(&arr[partitionIndex + 1], &arr[low + length]);
    return partitionIndex + 1;
}


// low and high are the index value
void quicksort(int arr[], int low, int high) {
    if (low < high) {
        int partitionIndex = partition(arr, low, high);

        quicksort(arr, low, partitionIndex - 1);
        quicksort(arr, partitionIndex + 1, high);
    }
}

void quicksortDriver() {
    int arr[] = {10, 7, 8, 9, 1, 5};
    int high = sizeof(arr) / sizeof(arr[0]);
    quicksort(arr, 0, high - 1);
    for (int i = 0; i < high; ++i) {
        std::cout << arr[i] << " ";
    }

}


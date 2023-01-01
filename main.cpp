#include <iostream>
#include <cstddef>
#include <chrono>
#include "array.h"
#include "quicksort.h"

const size_t SIZE = 1000000;

int main() {

    int *arr = createArray(SIZE);

    std::cout << "Initial:" << std::endl;
    printArray(arr, SIZE);

    auto start = std::chrono::high_resolution_clock::now();
    quickSort(arr, SIZE);
    auto finish = std::chrono::high_resolution_clock::now();

    std::chrono::duration<double> elapsed = finish - start;

    std::cout << "Sorted" << std::endl;
    printArray(arr, SIZE);
    std::cout << "Sorting array with size " << SIZE << " took " << elapsed.count() << " sec." << std::endl;

    return 0;
}

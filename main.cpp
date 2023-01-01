#include <iostream>
#include <cstddef>
#include "array.h"
#include "quicksort.h"

const size_t SIZE = 1000000;

int main() {

    int *arr = createArray(SIZE);

    std::cout << "Initial:" << std::endl;
    printArray(arr, SIZE);

    quickSort(arr, SIZE);

    std::cout << "Sorted" << std::endl;
    printArray(arr, SIZE);

    return 0;
}

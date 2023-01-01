#include <iostream>
#include <cstddef>
#include <ctime>
#include <random>
#include "array.h"

const int RND_MAX = 10000;
int getRandom();

int* createArray(const size_t size)
{
    int *arr = new int[size];

    for(size_t i = 0; i < size; ++i)
    {
        *(arr + i) = getRandom();
    }

    return arr;

}

void printArray(const int *arr, const size_t size)
{
    for(size_t i = 0; i < size; ++i)
    {
        std::cout << *(arr + i);
        if(i < size - 1)
        {
            std::cout << ' ';
        }
    }
    std::cout << std::endl;
}

int getRandom()
{
    static bool initiated = false;

    if(!initiated)
    {
        srand(time(nullptr));
        initiated = true;
    }

    return rand() % (2 * RND_MAX) - RND_MAX;
}
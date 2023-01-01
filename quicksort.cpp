#include <cstddef>
#include "quicksort.h"
#include "RequestHandler.h"
#include "TaskMonitor.h"

const size_t THREAD_BOUND = 10000;

RequestHandler rh;

void swap(int*, int*);
void qSort(int*, int*, TaskMonitor&);

void quickSort(int *arr, const size_t size)
{
    TaskMonitor monitor(size);
    qSort(arr, arr + size - 1, monitor);
    monitor.wait();
}

void qSort(int *first, int *last, TaskMonitor &monitor)
{
    if(first < last)
    {
        int *left = first - 1;

        for(int *item = first; item < last; ++item)
        {
            if(*item <= *last)
            {
                swap(++left, item);
            }
        }
        swap(++left, last);

        if(left - 1 - first >= THREAD_BOUND)
        {
            rh.pushRequest(qSort, first, left - 1, monitor);
            qSort(left, last, monitor);
        }
        else if(last - left >= THREAD_BOUND)
        {
            rh.pushRequest(qSort, left, last, monitor);
            qSort(first, left - 1, monitor);

        }
        else
        {
            qSort(first, left - 1, monitor);
            qSort(left, last, monitor);
        }
    }
    else
    {
        monitor.decreaseThreadCounter();
    }
}

void swap(int *a, int *b)
{
    if(*a == *b) return;

    *a ^= *b;
    *b ^= *a;
    *a ^= *b;
}
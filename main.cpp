#include <iostream>
#include <thread>
#include <mutex>
#include <chrono>
#include <ctime>
#include <random>
#include <vector>

#include "RequestHandler.h"
#include "ThreadPool.h"
#include "InterruptableThread.h"

std::mutex coutLocker;

void taskFunc(int id, int delay)
{
    for(int i = 0; i < delay; ++i)
    {
        if(InterruptableThread::checkInterrupted())
        {
            std::unique_lock<std::mutex> lock(coutLocker);
            std::cout << "Task " << id << " was interrupted" << std::endl;
        }
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }

    std::unique_lock<std::mutex> lock(coutLocker);
    std::cout << "Task " << id << " made by thread_id " << std::this_thread::get_id() << std::endl;
}

int main() {
    srand(time(nullptr));

    RequestHandler rh;
    std::vector<res_type> results;

    for(int i = 0; i < 20; ++i)
    {
        results.push_back(rh.pushRequest(taskFunc, i, rand() % 10));
    }

//    std::this_thread::sleep_for(std::chrono::seconds(1));
//    rh.interruptPool();

    for(auto &r: results)
    {
        r.wait();
    }

    return 0;
}

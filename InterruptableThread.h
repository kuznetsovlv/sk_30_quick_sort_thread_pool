#pragma once
#include <thread>
#include <chrono>
#include <mutex>

#include "ThreadPool.h"
#include "InterruptNotificator.h"

class ThreadPool;

class InterruptableThread
{
private:
    std::mutex _defender;
    bool* _pFlag;
    std::thread _thread;
    InterruptNotificator _notificator;


    void startFunc(ThreadPool*, size_t);

public:
    InterruptableThread(ThreadPool*, size_t);
    ~InterruptableThread();

    static bool checkInterrupted();

    void interrupt();
    void join();
};

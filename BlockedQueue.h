#pragma once
#include <queue>
#include <mutex>
#include <condition_variable>
#include "InterruptNotificator.h"

template<class T>
class BlockedQueue
{
private:
    std::mutex _locker;
    std::queue<T> _task_queue;
    std::condition_variable _notifier;

public:
    void push(T&);
    void pop(T&, InterruptNotificator&);
    bool fast_pop(T&);
};

#include "BlockedQueue.cpp"

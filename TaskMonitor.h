#pragma once
#include <mutex>
#include <future>

class TaskMonitor {
private:
    size_t _threadCounter;
    std::promise<void> _promise;
    std::mutex _defender;

public:
    TaskMonitor(size_t);

    void wait();
    void decreaseThreadCounter()noexcept;
};
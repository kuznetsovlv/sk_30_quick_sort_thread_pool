#include <mutex>
#include "TaskMonitor.h"

TaskMonitor::TaskMonitor(size_t size):_threadCounter(size)
{
}

void TaskMonitor::wait()
{
    _promise.get_future().wait();
}

void TaskMonitor::decreaseThreadCounter() noexcept
{
    std::lock_guard<std::mutex> lock(_defender);
    --_threadCounter;
    if(!_threadCounter)
    {
        _promise.set_value();
    }
}
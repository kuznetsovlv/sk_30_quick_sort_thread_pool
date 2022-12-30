#include <mutex>
#include <thread>

#include "InterruptableThread.h"
#include "ThreadPool.h"

thread_local bool thread_interrupt_flag = false;

InterruptableThread::InterruptableThread(ThreadPool *pool, size_t qindex):_pFlag(nullptr),_thread(&InterruptableThread::startFunc, this, pool, qindex)
{
}

InterruptableThread::~InterruptableThread()
{
    _thread.join();
}

void InterruptableThread::interrupt()
{
    std::lock_guard<std::mutex> lock(_defender);
    if(_pFlag)
    {
        *_pFlag = true;
        _notificator.notify();
    }
}

void InterruptableThread::startFunc(ThreadPool* pool, size_t qindex)
{
    {
        std::lock_guard<std::mutex> lock(_defender);
        _pFlag = &thread_interrupt_flag;
    }
   pool->threadFunc(qindex, _notificator);
    {
        std::lock_guard<std::mutex> lock(_defender);
        _pFlag = nullptr;
    }
}

void InterruptableThread::join()
{
    _thread.join();
}

bool InterruptableThread::checkInterrupted()
{
    return thread_interrupt_flag;
}

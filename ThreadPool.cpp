#include <mutex>

#include "ThreadPool.h"
#include "InterruptableThread.h"
#include "InterruptNotificator.h"
#include "TaskMonitor.h"

Task::Task():_task(nullptr)
{
}

Task::Task(task_type task):_task(task)
{
}

void Task::perform()
{
    if(_task)
    {
        _task();
        _promise.set_value();
    }
}

res_type Task::getResult() {
    return _promise.get_future();
}

bool Task::valid() const noexcept
{
    return !!_task;
}

ThreadPool::ThreadPool():_thread_count(std::thread::hardware_concurrency() ? std::thread::hardware_concurrency() : 4 ),_thread_queues(_thread_count),_task_count(0)
{
}

void ThreadPool::start()
{
    for(size_t i = 0; i < _thread_count; ++i)
    {
        _threads.push_back(new InterruptableThread(this, i));
    }
}

void ThreadPool::stop()
{
    for(auto &t: _thread_queues)
    {
        Task empty;
        t.push(empty);
    }
    for(auto &t: _threads)
    {
        t->join();
    }
}

res_type ThreadPool::push_task(FuncType f, int id, int arg)
{
    return push_task([=](){f(id, arg);});
}

res_type ThreadPool::push_task(FuncTypeTask f, bool arg1, bool arg2, bool arg3)
{
    return push_task([=](){f(arg1, arg2, arg3);});
}

res_type ThreadPool::push_task(FuncTypeArr f, int *beg, int *end, TaskMonitor &monitor)
{
    return push_task([=, &monitor](){f(beg, end, monitor);});
}

res_type ThreadPool::push_task(task_type taskFunc)
{
   Task task(taskFunc);
   auto res = task.getResult();
    size_t queue_to_push = _task_count++ % _thread_count;
    _thread_queues[queue_to_push].push(task);
    return res;
}

void ThreadPool::threadFunc(size_t qindex, InterruptNotificator &notificator)
{
    while (true)
    {
        if(InterruptableThread::checkInterrupted())
        {
            return;
        }
        Task task_to_do;
        bool res;
        size_t i = 0;
        for(; i < _thread_count; ++i)
        {
            if(res = _thread_queues[(qindex + i) % _thread_count].fast_pop(task_to_do))
            {
                break;
            }
        }

        if(!res)
        {
            _thread_queues[qindex].pop(task_to_do, notificator);
        } else if(!task_to_do.valid())
        {
            _thread_queues[(qindex + i) % _thread_count].push(task_to_do);
        }
        if(!task_to_do.valid())
        {
            return;
        }
        task_to_do.perform();
    }
}

void ThreadPool::interrupt()
{
    for(auto &t: _threads)
    {
        t->interrupt();
    }
}

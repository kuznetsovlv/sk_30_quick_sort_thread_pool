#pragma once
#include <future>
#include <vector>
#include <functional>

#include "BlockedQueue.h"
#include "InterruptableThread.h"
#include "InterruptNotificator.h"
#include "TaskMonitor.h"

typedef std::function<void()> task_type;
typedef std::future<void> res_type;
typedef void (*FuncType) (int, int);
typedef void (*FuncTypeTask) (bool, bool, bool);
typedef void (*FuncTypeArr) (int*, int*, TaskMonitor&);

class Task
{
private:
    task_type _task;
    std::promise<void> _promise;

public:
    Task();
    Task(task_type);

    void perform();
    bool valid()const noexcept;
    res_type getResult();
};

class InterruptableThread;

class ThreadPool
{
private:
    size_t _thread_count;
    std::vector<InterruptableThread*> _threads;
    std::vector<BlockedQueue<Task>> _thread_queues;
    size_t _task_count;

    res_type push_task(task_type);

public:
    ThreadPool();

    void start();
    void stop();
    res_type push_task(FuncType, int, int);
    res_type push_task(FuncTypeTask, bool, bool, bool);
    res_type push_task(FuncTypeArr, int*, int*, TaskMonitor&);
    void threadFunc(const size_t, InterruptNotificator&);
    void interrupt();
};

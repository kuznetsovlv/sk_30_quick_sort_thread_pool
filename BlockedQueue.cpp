#include <mutex>
#include <utility>
#include "BlockedQueue.h"
#include "InterruptNotificator.h"

template<class T>
void BlockedQueue<T>::push(T &item)
{
    std::lock_guard<std::mutex> lock(_locker);
    _task_queue.push(std::move(item));
    _notifier.notify_one();
}

template<class T>
void BlockedQueue<T>::pop(T &item, InterruptNotificator& notificator )
{
    std::unique_lock<std::mutex> lock(_locker);
    if(_task_queue.empty())
    {
        notificator.setNotifier(&_notifier);
        _notifier.wait(lock, [this, &notificator](){return !_task_queue.empty() || notificator.isInterrupted();});
    }
    if(!_task_queue.empty())
    {
        item = std::move(_task_queue.front());
        _task_queue.pop();
    }
}

template<class T>
bool BlockedQueue<T>::fast_pop(T &item)
{
    std::lock_guard<std::mutex> lock(_locker);
    if(_task_queue.empty())
    {
        return false;
    }

    item = std::move(_task_queue.front());
    _task_queue.pop();
    return true;
}
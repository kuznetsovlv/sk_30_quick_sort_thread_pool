#include <condition_variable>
#include <mutex>
#include "InterruptNotificator.h"
#include "InterruptableThread.h"

InterruptNotificator::InterruptNotificator():_notifier(nullptr)
{
}

void InterruptNotificator::setNotifier(std::condition_variable *notifier)noexcept
{
    std::lock_guard<std::mutex> lock(_defender);
    _notifier = notifier;
}

void InterruptNotificator::notify()noexcept
{
    std::lock_guard<std::mutex> lock(_defender);
    if(_notifier)
    {
        _notifier->notify_one();
        _notifier = nullptr;
    }
}

bool InterruptNotificator::isInterrupted()const noexcept {
    return InterruptableThread::checkInterrupted();
}
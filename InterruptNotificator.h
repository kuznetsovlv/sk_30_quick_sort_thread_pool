#pragma once
#include <condition_variable>
#include <mutex>

class InterruptNotificator
{
private:
    std::condition_variable *_notifier;
    std::mutex _defender;

public:
    explicit InterruptNotificator();

    void setNotifier(std::condition_variable*)noexcept;
    void notify()noexcept;
    bool isInterrupted()const noexcept;
};

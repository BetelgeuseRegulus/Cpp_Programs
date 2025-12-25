#include "framework/TimerManager.h"

namespace LightYears
{

    unsigned int TimerHandle::timerKeyCounter_ = 0;

    TimerHandle::TimerHandle()
        : timerKey_{GetNextTimerKey_()}
    {
    }

    bool operator==(const TimerHandle &lhs, const TimerHandle &rhs)
    {
        return lhs.GetTimeKey() == rhs.GetTimeKey();
    }

    //============================================================================================

    Timer::Timer(weak<Object> weakRef, std::function<void()> callback, float duration, bool repeat)
        : listener_{weakRef, callback},
          duration_{duration},
          repeat_{repeat},
          timeCounter_{0.f},
          isExpired_{false}
    {
    }

    void Timer::TickTime(float deltaTime)
    {
        if (Expired())
        {
            return;
        }

        timeCounter_ += deltaTime;
        if (timeCounter_ >= duration_)
        {
            listener_.second();
            if (repeat_)
            {
                timeCounter_ = 0.f;
            }
            else
            {
                SetExpired();
            }
        }
    }

    bool Timer::Expired() const
    {
        return isExpired_ || listener_.first.expired() || listener_.first.lock()->IsPendingDestory();
    }

    void Timer::SetExpired()
    {
        isExpired_ = true;
    }

    //============================================================================================

    unique<TimerManager> TimerManager::timerManager_{nullptr};

    TimerManager::TimerManager()
        : timers_{}
    {
    }

    TimerManager &TimerManager::Get()
    {
        if (!timerManager_)
        {
            timerManager_ = std::move(unique<TimerManager>(new TimerManager{}));
        }

        return *timerManager_;
    }

    void TimerManager::UpdateTimer(float deltaTime)
    {
        for (auto iter = timers_.begin(); iter != timers_.end();)
        {
            if (iter->second.Expired())
            {
                iter = timers_.erase(iter);
            }
            else
            {
                iter->second.TickTime(deltaTime);
                ++iter;
            }
        }
    }

    void TimerManager::ClearTimer(TimerHandle timeHandle)
    {
        auto iter = timers_.find(timeHandle);

        if (iter != timers_.end())
        {
            iter->second.SetExpired();
        }
    }
}
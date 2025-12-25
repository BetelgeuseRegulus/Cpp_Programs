#pragma once
#include <functional>

#include "framework/Core.h"
#include "framework/Object.h"

namespace LightYears
{
    struct TimerHandle
    {
        TimerHandle();
        unsigned int GetTimeKey() const { return timerKey_; }

    private:
        static unsigned int GetNextTimerKey_() { return ++timerKeyCounter_; };

    private:
        unsigned int timerKey_{};
        static unsigned int timerKeyCounter_;
    };

    struct TimerHandleHashFunction
    {
    public:
        std::size_t operator()(const TimerHandle &timerHandle) const
        {
            return timerHandle.GetTimeKey();
        }
    };

    bool operator==(const TimerHandle &lhs, const TimerHandle &rhs);

    // ===============================================================================================
    struct Timer
    {
        Timer(weak<Object> weakRef, std::function<void()> callback, float duration, bool repeat);

        void TickTime(float deltaTime);

        bool Expired() const;
        void SetExpired();

    private:
        std::pair<weak<Object>, std::function<void()>> listener_;
        float duration_{};
        bool repeat_{};
        float timeCounter_{};
        bool isExpired_{};
    };

    // ===============================================================================================
    class TimerManager
    {
    public:
        static TimerManager &Get();

        template <typename ClassName>
        TimerHandle SetTimer(weak<Object> weakRef, void (ClassName::*callback)(), float duration, bool repeat = false)
        {
            TimerHandle newHandle{};
            timers_.insert({newHandle,
                            Timer(weakRef, [=]
                                  { (static_cast<ClassName *>(weakRef.lock().get())->*callback)(); }, duration, repeat)});
            return newHandle;
        }

        void UpdateTimer(float deltaTime);
        void ClearTimer(TimerHandle timerHandle);

    protected:
        TimerManager();

    private:
    private:
        static unique<TimerManager> timerManager_;

        Dictionary<TimerHandle, Timer, TimerHandleHashFunction> timers_;
    };
}
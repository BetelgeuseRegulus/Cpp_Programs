#pragma once

#include <memory>

#include "framework/Core.h"
#include "framework/Delegate.h"

namespace LightYears
{
    // std::enable_shared_from_this<Object> 有返回一个 week_ptr的函数
    class Object : public std::enable_shared_from_this<Object>
    {
    public:
        Object();
        virtual ~Object();

        virtual void Destroy();
        bool IsPendingDestory() const { return isPendingDestory_; }

        weak<Object> GetWeakRef();
        weak<const Object> GetWeakRef() const;

        unsigned int GetUniqueID() const { return uniqueID_; }

    public:
        Delegate<Object *> onDestory_;

    private:
        static unsigned int GetNextAvaliableID();

    private:
        bool isPendingDestory_{};
        unsigned int uniqueID_;

        static unsigned int uniqueIDCounter_;
    };
} // namespace LightYears

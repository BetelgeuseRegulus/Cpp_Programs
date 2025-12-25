#pragma once
#include <functional>

#include "framework/Core.h"

namespace LightYears
{
    class Object;
    /**
     * @brief 委托类，用于实现观察者模式的事件系统
     *
     * 允许多个对象订阅同一个事件，当事件触发时广播给所有订阅者
     * 使用 weak_ptr 避免循环引用，当对象销毁时自动清理失效的回调
     *
     * @tparam Args 回调函数的参数类型（可变参数）
     */
    template <typename... Args>
    class Delegate
    {
    public:
        /**
         * @brief 绑定一个对象的成员函数作为回调
         *
         * 将对象的成员函数注册到委托中，当 Broadcast 被调用时会执行该函数
         * 使用 weak_ptr 持有对象，避免延长对象生命周期
         *
         * @tparam ClassName 对象的类型（必须继承自 Object）
         * @param obj 对象的弱引用
         * @param callback 成员函数指针
         *
         * @note 当对象被销毁后，对应的回调会在下次 Broadcast 时自动清理
         */
        template <typename ClassName>
        void BindAction(weak<Object> obj, void (ClassName::*callback)(Args...))
        {
            std::function<bool(Args...)> callbackFunc = [obj, callback](Args... args) -> bool
            {
                // 如果传入的对象存在, 转换 obj 为 ClassName 并调用传入的其成员函数 callback
                if (!obj.expired())
                {
                    (static_cast<ClassName *>(obj.lock().get())->*callback)(args...);
                    return true;
                }

                return false;
            };

            callbacks_.push_back(callbackFunc);
        }

        /**
         * @brief 广播事件给所有订阅者
         *
         * 遍历所有已绑定的回调函数并执行
         * 如果某个回调对应的对象已销毁（返回 false），则自动从列表中移除
         *
         * @param args 传递给回调函数的参数
         *
         * @note 此方法会自动清理失效的回调（对象已销毁的）
         */
        void Broadcast(Args... args)
        {
            // 遍历并调用 callback 的所有函数 -> 广播所有函数(Boardcast)
            for (auto iter = callbacks_.begin(); iter != callbacks_.end();)
            {
                if ((*iter)(args...))
                {
                    ++iter;
                }
                else
                {
                    iter = callbacks_.erase(iter);
                }
            }
        }

        /**
         * @brief 清除所有已绑定的回调函数
         *
         * 移除所有订阅者，通常在对象销毁时调用以避免悬空引用
         *
         * @note 调用此方法后，Delegate 将不再持有任何回调
         */
        void Clear()
        {
            callbacks_.clear();
        }

    private:
        List<std::function<bool(Args...)>> callbacks_;
    };
}
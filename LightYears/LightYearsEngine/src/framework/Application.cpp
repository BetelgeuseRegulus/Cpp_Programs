#include <iostream>
#include <cstdio>

#include "framework/Application.h"
#include "framework/Core.h"
#include "framework/World.h"
#include "framework/AssetManager.h"
#include "framework/PhysicsSystem.h"
#include "framework/TimerManager.h"

namespace LightYears
{
    Application::Application(unsigned int windowWidth, unsigned int windowHeight, const std::string &title, sf::Uint32 style)
        : window_{sf::VideoMode(windowWidth, windowHeight), title, style},
          targetFrameRate_{60.f},
          tickClock_{},
          currentWorld_{nullptr},
          pendingWorld_{nullptr},
          cleanCycleClock_{},
          cleanCycleIterval_{0.5f}
    {
    }

    void Application::run()
    {
        tickClock_.restart();
        float accumulatedTime = 0.f;                    // 记录上一帧到当前帧的累计时间
        float targetDeltaTime = 1.f / targetFrameRate_; // 1 / 60fps 表示60帧时每一帧消耗的时间

        while (window_.isOpen())
        {
            sf::Event windowEvent;

            while (window_.pollEvent(windowEvent))
            {
                if (windowEvent.type == sf::Event::EventType::Closed)
                {
                    QuitApplication();
                }
                else
                {
                    DispathEvent(windowEvent);
                }
            }

            // 每当累积时间超过目标帧时间，就认为可以更新一帧游戏逻辑
            float frameDeltaTime = tickClock_.restart().asSeconds();
            accumulatedTime += frameDeltaTime;
            while (accumulatedTime > targetDeltaTime)
            {
                accumulatedTime -= targetDeltaTime;
                TickInternal(targetDeltaTime);
                RenderInternal();
            }
        }
    }

#pragma region custom
    void Application::TickInternal(float deltaTime)
    {
        // ✅ 关键修改：在 Tick 之前切换 World
        if (pendingWorld_ && pendingWorld_ != currentWorld_)
        {
            // 销毁旧 World
            if (currentWorld_)
            {
                currentWorld_->BeginDestroy(); // 标记所有对象为待销毁
                currentWorld_->CleanCycle();   // 立即清理
            }

            // 切换到新 World
            currentWorld_ = pendingWorld_;
            pendingWorld_ = nullptr;

            // 清理物理系统
            PhysicsSystem::Get().Cleanup();

            // 启动新 World
            currentWorld_->BeginPlayInternal();
        }

        // 更新应用层逻辑
        Tick(deltaTime);

        // 更新当前 World
        if (currentWorld_)
        {
            currentWorld_->TickInternal(deltaTime);
        }

        // 更新定时器
        TimerManager::Get().UpdateTimer(deltaTime);

        // 更新物理系统
        PhysicsSystem::Get().Step(deltaTime);

        // 定期清理周期
        if (cleanCycleClock_.getElapsedTime().asSeconds() >= cleanCycleIterval_)
        {
            cleanCycleClock_.restart();
            AssetManager::Get().CleanCycle();
            if (currentWorld_)
            {
                currentWorld_->CleanCycle();
            }
        }
    }
#pragma endregion

    // void Application::TickInternal(float deltaTime)
    // {
    //     Tick(deltaTime);
    //     if (currentWorld_)
    //     {
    //         currentWorld_->TickInternal(deltaTime);
    //     }
    //
    //     TimerManager::Get().UpdateTimer(deltaTime);
    //     PhysicsSystem::Get().Step(deltaTime);
    //
    //     if (cleanCycleClock_.getElapsedTime().asSeconds() >= cleanCycleIterval_)
    //     {
    //         cleanCycleClock_.restart();
    //         AssetManager::Get().CleanCycle();
    //
    //         if (currentWorld_)
    //         {
    //             currentWorld_->CleanCycle();
    //         }
    //     }
    //
    //     if (pendingWorld_ && pendingWorld_ != currentWorld_)
    //     {
    //         currentWorld_ = pendingWorld_;
    //
    //         PhysicsSystem::Get().Cleanup();
    //         currentWorld_->BeginPlayInternal();
    //     }
    // }

    void Application::RenderInternal()
    {

        window_.clear();
        Render();
        window_.display();
    }

    void Application::Tick(float deltaTime)
    {
    }

    void Application::Render()
    {
        if (currentWorld_)
        {
            currentWorld_->Render(window_);
        }
    }

    bool Application::DispathEvent(const sf::Event &event)
    {
        if (currentWorld_)
        {
            return currentWorld_->DispathEvent(event);
        }

        return false;
    }

    sf::Vector2u Application::GetWindowSize() const
    {
        return window_.getSize();
    }

    void Application::QuitApplication()
    {
        window_.close();
    }

} // namespace lightYear

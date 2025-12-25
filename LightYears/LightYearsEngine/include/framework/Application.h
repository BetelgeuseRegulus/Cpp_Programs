#pragma once
#include <SFML/Graphics.hpp>
#include "framework/Core.h"
#include "framework/World.h"

namespace LightYears
{
    class World;
    /**
     * @brief 应用程序主类,管理游戏窗口,主循环和世界(World)的声明周期
     *
     * Application是游戏引擎的核心类，负责：
     * - 创建和管理SFML渲染窗口
     * - 控制游戏主循环（更新和渲染）
     * - 管理帧率
     * - 加载和切换游戏世界(World)
     * - 执行定期清理任务
     */
    class Application
    {
    public:
        Application(unsigned int windowWidth, unsigned int windowHeight, const std::string &title, sf::Uint32 style);

        /**
         * @brief 启动游戏主循环
         *
         */
        void run();

        /**
         * @brief 加载并切换到新的游戏世界
         *
         * @tparam WorldType 要加载的 World类型, 必须继承自 World类
         * @return weak<WorldType> 返回新创建的 World的 weak_ptr
         */
        template <typename WorldType>
        weak<WorldType> LoadWorld();

        sf::Vector2u GetWindowSize() const;

        sf::RenderWindow &GetWindow() { return window_; }
        const sf::RenderWindow &GetWindow() const { return window_; }

        void QuitApplication();

    private:
        bool DispathEvent(const sf::Event &event);

        /**
         * @brief 每帧更新内部函数
         *
         * @param deltaTime 距离上一帧的时间间隔(秒)
         *
         */
        void TickInternal(float deltaTime);
        /**
         * @brief 渲染内部函数
         *
         * 清空窗口，调用虚函数Render()和当前World的Render()进行绘制，然后显示到屏幕
         */
        void RenderInternal();

        /**
         * @brief 每帧更新的虚函数
         *
         * @param deltaTime 距离上一帧的时间间隔（秒）
         *                  deltaTime = 当前帧开始时间 - 上一帧开始时间
         *
         * 子类可以重写此函数来实现应用程序级别的自定义更新逻辑。
         */
        virtual void Tick(float deltaTime);
        /**
         * @brief 渲染的虚函数
         *
         * 子类可以重写此函数来实现应用程序级别的自定义渲染逻辑。
         */
        virtual void Render();

    private:
        /**
         * @brief SFML 渲染窗口
         *
         */
        sf::RenderWindow window_{};
        /**
         * @brief 目标帧率(帧/秒),用于控制游戏运行速度,通常设置为60帧
         *
         */
        float targetFrameRate_{};
        /**
         * @brief 计时器, 用于计算每帧的 daltaTime
         *
         */
        sf::Clock tickClock_{};

        /**
         * @brief 当前激活的游戏世界(World)的 shared_ptr
         *
         */
        shared<World> currentWorld_{};
        shared<World> pendingWorld_{};

        /**
         * @brief 清理周期计时器, 用于追踪距离上次清理的时间
         *
         */
        sf::Clock cleanCycleClock_{};
        /**
         * @brief 清理周期间隔(秒), 定义多久执行一次内存清理或资源管理任务
         *
         */
        float cleanCycleIterval_{};
    };

    template <typename WorldType>
    weak<WorldType> Application::LoadWorld()
    {
        shared<WorldType> newWorld{new WorldType{this}};
        // 不要立即切换，而是设置为 pending
        pendingWorld_ = newWorld;

        // ❌ 删除这两行
        // currentWorld_ = newWorld;
        // currentWorld_->BeginPlayInternal();

        return newWorld;
    }
}
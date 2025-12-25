#pragma once
#include <SFML/Graphics.hpp>

#include "framework/Core.h"
#include "framework/Object.h"

namespace LightYears
{
    class Actor;
    class Application;
    class HUD;
    class GameStage;
    /**
     * @brief 游戏世界类, 管理所有游戏对象(Actor)的容器
     *
     */
    class World : public Object
    {
    public:
        World(Application *owningApp);

        /**
         * @brief  游戏启动内部函数
         *
         * 在游戏循环开始前调用，用于初始化World和所有Actor。
         * 会调用虚函数BeginPlay()以及所有Actor的BeginPlay。
         */
        void BeginPlayInternal();
        /**
         * @brief 每帧更新函数内部函数
         *
         * @param deletTime 距离上一帧的时间间隔(秒)
         *
         * 在每一帧调用，用于更新 World和所有 Actor的状态。
         * 会调用虚函数 Tick()以及所有 Actor的 Tick。
         * 同时处理 pendingActors_队列，将新创建的 Actor加入到主 actors_列表
         */
        void TickInternal(float deletTime);
        /**
         * @brief 渲染 world中的所有 Actor
         *
         * @param window SFML渲染窗口调用
         *
         * 遍历所有 Actor 并调用他们的 Render() 函数进行绘制
         */
        void Render(sf::RenderWindow &window);

        virtual ~World();

        /**
         * @brief 在 World 中生成一个新的 Actor
         *
         * @tparam ActorType 要生成的 Actor类型, 必须继承自 Actor类
         * @return weak<ActorType> 返回新创建的 std::weal_ptr<>
         */
        template <typename ActorType, typename... Args>
        weak<ActorType> SpawnActor(Args... args);

        template <typename HUDType, typename... Args>
        weak<HUDType> SpawnHUD(Args... args);

        sf::Vector2u GetWindowSize() const;

        void CleanCycle();
        void AddStage(const shared<GameStage> &newStage);
        bool DispathEvent(const sf::Event &evnet);

        Application *GetApplication() { return owningApp_; }
        const Application *GetApplication() const { return owningApp_; }

        void BeginDestroy();

        bool GetIsBeingDestroyed() const { return isBeingDestroyed_; }

    private:
        /**
         * @brief 虚函数 游戏启动函数
         *
         * 子类可以重写此函数来实现自定义的游戏启动初始化逻辑
         */
        virtual void BeginPlay();
        /**
         * @brief 虚函数 游戏每帧更新函数
         *
         * @param deletTime 距离i上一帧的时间间隔(秒)
         *
         * 子类可以重写此函数来实现自定义的每帧更新逻辑
         */
        virtual void Tick(float deletTime);
        virtual void RenderHUD(sf::RenderWindow &window);

        virtual void InitGameStages();
        virtual void AllGameStageFinished();

        void NextGameStage();
        void StartStages();

    private:
        /**
         * @brief 拥有此 world的 Application 指针
         *
         */
        Application *owningApp_{};
        /**
         * @brief 标记 World是否已经开始运行(是否已经调用 BeginPlay())
         *
         */
        bool beganPlay_{};

        /**
         * @brief 当前活跃的 Actor列表, 存储所有正在运行的 Actor 的 sheard指针
         *
         */
        List<shared<Actor>> actors_{};
        /**
         * @brief 待处理的 Actor对象列表, 新创建的 Actor会先加入此队列, 在下一帧转移到 actors_ 列表中.
         *
         */
        List<shared<Actor>> pendingActors_{};

        List<shared<GameStage>> gameStages_{};

        List<shared<GameStage>>::iterator currentStage_{};

        shared<HUD> HUD_;

        bool isBeingDestroyed_{false};
    };

    /**
     * @brief 在 World 中生成一个新的指定类型的 Actor
     *
     * 可变参数模板 Variadic Templates
     * 使用可变参数模板支持传递任意数量的构造函数参数。
     * World* 会自动作为第一个参数传递给 Actor 构造函数。
     *
     * @tparam ActorType 要生成的 Actor 类型（必须继承自 Actor）
     * @tparam Args 可变参数类型包，转发给 ActorType 构造函数
     * @param args 传递给 ActorType 构造函数的参数（World* 之后的参数）
     * @return weak<ActorType> 指向新创建 Actor 的弱引用指针
     */
    template <typename ActorType, typename... Args>
    weak<ActorType> World::SpawnActor(Args... args)
    {
        shared<ActorType> newActor{new ActorType{this, args...}};
        pendingActors_.push_back(newActor);
        return newActor;
    }

    template <typename HUDType, typename... Args>
    inline weak<HUDType> World::SpawnHUD(Args... args)
    {
        shared<HUDType> newHUD{new HUDType(args...)};
        HUD_ = newHUD;
        return newHUD;
    }
}
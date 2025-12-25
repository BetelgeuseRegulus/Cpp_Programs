#pragma once
#include <SFML/Graphics.hpp>
#include <box2d/b2_body.h>

#include "framework/Object.h"
#include "framework/Core.h"
#include "framework/Delegate.h"

namespace LightYears
{

    class World;
    /**
     * @brief 游戏中所有可交互对象的基类
     *
     * Actor是游戏世界中的基本实体单元，代表场景中可见的、可更新的游戏对象。
     * 所有游戏中的角色、敌人、道具、子弹等都应继承自Actor类。
     */
    class Actor : public Object
    {
    public:
        Actor(World *owingWorld, const std::string &texturePath = "");
        virtual ~Actor();

        /**
         * @brief 游戏开始内部函数
         *
         * 由World在将Actor添加到场景时调用（从pendingActors_转移到actors_时）。
         * 设置hasBeganPlay_标志为true，并调用虚函数BeginPlay()。
         * 此函数只会被调用一次。
         *
         */
        void BeginPlayInternal();
        /**
         * @brief 每帧更新内部函数
         *
         * @param deltaTime 距离上一帧的时间间隔（秒）
         *
         * 由World在每帧调用，用于更新Actor的状态。
         * 调用虚函数Tick()，子类可以重写Tick()实现自定义逻辑。
         */
        void TickInternal(float deltaTime);

        /**
         * @brief 游戏开始时调用的虚函数
         *
         * 在Actor被添加到游戏世界后立即调用一次，用于初始化Actor
         */
        virtual void BeginPlay();
        /**
         * @brief 每帧更新的虚函数
         *
         * @param deltaTime 距离上一帧的时间间隔（秒）
         *
         * 每帧调用一次，用于更新Actor的状态和行为
         */
        virtual void Tick(float deltaTime);

        /**
         * @brief 设置 Actor 的纹理
         *
         * @param texturePath 纹理文件路径
         */
        void SetTexture(const std::string &texturePath);
        /**
         * @brief 渲染函数, 将 Actor 渲染到窗口
         *
         * @param window SFML 窗口对象引用
         */
        virtual void Render(sf::RenderWindow &window);

        /**
         * @brief 设置 Actor 的位置(绝对坐标)
         *
         * @param newLoc 新的位置坐标(世界坐标系)
         *
         * 将Actor移动到指定的绝对位置
         */
        void SetActorLocation(const sf::Vector2f &newLoc);
        /**
         * @brief 设置 Actor 的旋转角度(绝对角度),单位 度
         *
         * @param newRot 新的旋转角度(度数, 0度向右, 顺时针为正)
         *
         * 将Actor旋转到指定的绝对角度
         */
        void SetActorRotation(float newRot);
        /**
         * @brief 添加位置偏移（相对移动）
         *
         * @param offsetAmt 位置偏移量向量
         *
         * 在当前位置的基础上移动Actor
         */
        void AddActorLocationOffset(const sf::Vector2f &offsetAmt);
        /**
         * @brief 添加旋转偏移（相对旋转）
         *
         * @param offsetAmt 旋转偏移量（度数）
         *
         * 在当前旋转角度的基础上旋转Actor
         */
        void AddActorRotationOffset(float offsetAmt);
        /**
         * @brief 获取Actor的当前位置
         *
         * @return sf::Vector2f Actor的(左上角)世界坐标位置
         */
        sf::Vector2f GetActorLocation() const;
        /**
         * @brief 获取Actor的当前旋转角度
         *
         * @return float Actor的旋转角度（度数）
         */
        float GetActorRotation() const;
        /**
         * @brief 获取Actor的前方方向向量
         *
         * @return sf::Vector2f 单位向量，表示Actor当前朝向的方向
         */
        sf::Vector2f GetActorForwardDirection() const;
        /**
         * @brief 获取Actor的右方方向向量
         *
         * @return sf::Vector2f 单位向量，表示Actor右侧的方向
         */
        sf::Vector2f GetActorRightDirection() const;

        void SetActorForwardDirection(float newForwardDirection);

        sf::FloatRect GetActorGlobalBounds() const;

        sf::Vector2u GetWindowSize() const;

        const World *GetWorld() const { return owningWorld_; }
        World *GetWorld() { return owningWorld_; }

        bool IsActorOutOfWindowBounds(float allowance = 10.f) const;

        void SetEnablePhysics(bool enable);

        virtual void OnActorBeginOverlap(Actor *other);
        virtual void OnActorEndOverlap(Actor *other);
        virtual void Destroy() override;

        static uint8 GetNeturalTeamID() { return NETURAL_TEAM_ID; }

        void SetTeamID(uint8 teamID) { teamID_ = teamID; }
        uint8 GetTeamID() const { return teamID_; }

        bool IsOtherHostile(Actor *other) const;

        virtual void ApplyDamage(float amt);

        sf::Sprite &GetSprite() { return sprite_; }
        const sf::Sprite &GetSprite() const { return sprite_; }

        void SetTextureRepeated(bool repeated);

    public:
        Delegate<Actor *> onActorDestoryed_;

    private:
        /**
         * @brief 将sprite的原点设置到纹理(几何)中心
         *
         * 在SetTexture()加载纹理后自动调用
         *
         */
        void CenterPivot();

        void InitializePhysics();
        void UnInitializePhysics();
        /**
         * @brief 将 Actor对象的位置和变换(旋转等), 转换成 Box2D 的物理坐标(米 + 弧度),并同步到 物理 Body.
         *
         */
        void UpdatePhysicsTransform();

    private:
        /**
         * @brief 用于此 Actor 的 World 指针, Actor必须属于某个 World
         *
         */
        World *owningWorld_{};
        /**
         * @brief 标记 Actor是否已经调用过 BeginPlay(),防止重复初始化
         *
         */
        bool hasBeganPlay_{};

        /**
         * @brief SFML Sprite对象, 用于渲染纹理到屏幕, 包含位置,旋转,缩放等变换信息.
         *
         */
        sf::Sprite sprite_{};
        /**
         * @brief Texture 的 shared_ptr, 存储 Actor 的视觉信息.
         *
         * 使用 shared_ptr 允许多个Actor共享使用同一个纹理.
         * 通过 AssetManager的缓存机制可以避免重复加载.
         *
         */
        shared<sf::Texture> texture_{};

        b2Body *physicsBody_{};
        bool physicsEnabled_{};

        uint8 teamID_;

        static constexpr uint8 NETURAL_TEAM_ID = 255;

        // my self variable
        sf::Vector2f forwardDirection_{};       // 逻辑上的朝向的方向向量（独立于视觉旋转）
        bool useCustomForwardDirection_{false}; // 是否使用自定义朝向
    };
} // namespace LightYears

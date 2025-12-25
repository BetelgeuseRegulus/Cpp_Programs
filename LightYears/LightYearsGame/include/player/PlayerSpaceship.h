#pragma once
#include "spaceship/Spaceship.h"
#include "framework/TimerManager.h"

namespace LightYears
{
    class Shooter;
    class ThreeWayShooter;
    class PlayerSpaceship : public Spaceship
    {
    public:
        static constexpr float move_up = -1.f;
        static constexpr float move_dowm = 1.f;
        static constexpr float move_left = -1.f;
        static constexpr float move_right = 1.f;

    public:
        PlayerSpaceship(World *owningWorld, const std::string &path = "SpaceShooterRedux/PNG/playerShip1_blue.png");
        ~PlayerSpaceship();

        virtual void Tick(float deletaTime) override;

        void SetSpeed(float newSpeed) { speed_ = newSpeed; }
        float GetSpeed() const { return speed_; }

        virtual void Shoot() override;

        void SetShooter(unique<Shooter> &&newShooter);

        virtual void ApplyDamage(float amt) override;
        virtual void BeginPlay() override;

    private:
        /**
         * @brief  获取输入
         *
         * 收集和读取输入（键盘/鼠标/手柄)
         *
         */
        void HandleInput();
        /**
         * @brief 校正输入
         *
         *  对输入进行有效性检查与范围限制
         *
         */
        void NormalizeInput();
        /**
         * @brief 限制输入
         *
         */
        void ClampInputOnEdge();
        /**
         * @brief 使用输入（驱动游戏行为）
         *
         * 将输入应用到角色/物体的运动逻辑中
         *
         * @param deltaTime 上一帧的时间间隔
         */
        void ConsumeInput(float deltaTime);

        void StopInvulnerable();
        void UpdateInvulnerable(float deltaTime);

    private:
        sf::Vector2f moveInput_{};
        float speed_{};

        unique<Shooter> shooter_;

        float invulnerableTimer_;
        TimerHandle invulnerableTimerHandle_;
        bool invulnerable_;

        float invulnerableFlashInterval_;
        float invulnerableFlashTimer_;
        float invulnerableFlashDir_;
    };
}
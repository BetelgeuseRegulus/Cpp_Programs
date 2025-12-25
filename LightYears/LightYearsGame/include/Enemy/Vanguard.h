#pragma once
#include "enemy/EnemySpaceship.h"

namespace LightYears
{
    class BulletShooter;
    /**
     * @brief 敌方飞船类型 : Vanguard/先锋
     *
     */
    class Vanguard : public EnemySpaceship
    {
    public:
        Vanguard(World *owningWorld,
                 const std::string &texturePath = "SpaceShooterRedux/PNG/Enemies/enemyBlue3.png",
                 const sf::Vector2f &velocity = {0.f, 150.f});
        virtual ~Vanguard();

        virtual void Tick(float daltaTime) override;

    private:
        virtual void Shoot() override;

        private:
        unique<BulletShooter> shooter_;
    };
}
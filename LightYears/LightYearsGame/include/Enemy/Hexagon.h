#pragma once
#include "enemy/EnemySpaceship.h"

namespace LightYears
{
    class BulletShooter;
    /**
     * @brief 敌方飞船类型: Hexagon/蜂巢,堡垒
     *
     */
    class Hexagon : public EnemySpaceship
    {
    public:
        Hexagon(World *owningWorld,
                const std::string &texturePath = "SpaceShooterRedux/PNG/Enemies/enemyGreen4.png",
                const sf::Vector2f &velocity = {0.f, 100.f});
        virtual ~Hexagon();

        virtual void Tick(float deltaTime) override;

    private:
        virtual void Shoot() override;

    private:
        unique<BulletShooter> shooter1_;
        unique<BulletShooter> shooter2_;
        unique<BulletShooter> shooter3_;
        unique<BulletShooter> shooter4_;
        unique<BulletShooter> shooter5_;
        unique<BulletShooter> shooter6_;
    };
}
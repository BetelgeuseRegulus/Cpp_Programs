#pragma once

#include "enemy/EnemySpaceship.h"
#include "framework/Core.h"

namespace LightYears
{
    class BulletShooter;
    /**
     * @brief 敌方飞船类型: TwinBlade/双刃
     *
     */
    class TwinBlade : public EnemySpaceship
    {
    public:
        TwinBlade(World *owningWorld,
                  const std::string &texturePath = "SpaceShooterRedux/PNG/Enemies/enemyBlack1.png",
                  const sf::Vector2f &velocity = {0.f, 120.f});

        virtual void Tick(float deltaTime) override;
        virtual void Shoot() override;

        ~TwinBlade();

    private:
        unique<BulletShooter> shooterLefr_;
        unique<BulletShooter> shooterRight_;
    };
}
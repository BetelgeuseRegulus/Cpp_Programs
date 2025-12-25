#pragma once
#include "Enemy/EnemySpaceship.h"

namespace LightYears
{
    class BulletShooter;
    class UFO : public EnemySpaceship
    {
    public:
        UFO(World *owningWorld,
            const sf::Vector2f &velocity,
            const std::string texturePath = "SpaceShooterRedux/PNG/ufoBlue.png",
            float rotationSpeed = 40.f);
        ~UFO();

        virtual void Tick(float deltaTime) override;

    private:
        virtual void Shoot() override;

    private:
        unique<BulletShooter> shooter1_;
        unique<BulletShooter> shooter2_;
        unique<BulletShooter> shooter3_;

        float rotationSpeed_{};
    };
}
#pragma once
#include <SFML/System.hpp>
#include "weapon/Shooter.h"

namespace LightYears
{
    class BulletShooter : public Shooter
    {
    public:
        BulletShooter(Actor *owner,
                      float cooldownTime = 1.f,
                      const sf::Vector2f &localPositionOffset = {0.f, 0.f},
                      float localRotationOffset = 0.f,
                      const std::string &bulletTexturePath = "SpaceShooterRedux/PNG/Lasers/laserBlue01.png");
        virtual ~BulletShooter();

        virtual bool IsOnCooldown() const override;
        virtual void IncrementLevel(int amt) override;
        void SetBulletTexturePath(const std::string &bulletTexturePath);

    private:
        virtual void ShootImpl() override;

    private:
        sf::Clock cooldownClock_{};
        float cooldownTime_{};

        sf::Vector2f localPositionOffset_{};
        float localRotationOffset_{};

        std::string bulletTexturePath_;
    };
} // namespace LightYears

#pragma once
#include <SFML/Graphics.hpp>
#include "weapon/BulletShooter.h"

namespace LightYears
{

    /**
     * @brief 武器类型: 三发弹
     *
     */
    class ThreeWayShooter : public Shooter
    {
    public:
        ThreeWayShooter(Actor *onwer,
                        float cooldownTime = 0.3f,
                        const sf::Vector2f &localOffset = {0.f, 0.f});
        ~ThreeWayShooter() = default;

        virtual void SetCurrentLevel(int level) override;

    private:
        virtual void ShootImpl() override;
        virtual void IncrementLevel(int amt) override;

    private:
        BulletShooter shooterLeft_;
        BulletShooter shooterMid_;
        BulletShooter shooterRight_;
        BulletShooter topLevelShooterLeft_;
        BulletShooter topLevelShooterRight_;
    };
}
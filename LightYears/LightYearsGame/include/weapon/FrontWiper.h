#pragma once
#include <SFML/Graphics.hpp>
#include "weapon/BulletShooter.h"

namespace LightYears
{
    /**
     * @brief 武器类型: 肃清者
     *
     */
    class FrontWiper : public Shooter
    {
    public:
        FrontWiper(Actor *ownerActor,
                   float cooldownTime = 0.3f,
                   const sf::Vector2f &localOffset = {0.f, 0.f},
                   float width = 60.f);

        virtual void SetCurrentLevel(int level) override;

    private:
        virtual void ShootImpl() override;
        virtual void IncrementLevel(int amt) override;

    private:
        float width_{}; // 子弹宽度

        BulletShooter shooter1_;
        BulletShooter shooter2_;
        BulletShooter shooter3_;
        BulletShooter shooter4_;

        BulletShooter shooter5_;
        BulletShooter shooter6_;
    };
}
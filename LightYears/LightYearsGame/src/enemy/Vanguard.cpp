#include "enemy/Vanguard.h"
#include "weapon/BulletShooter.h"

namespace LightYears
{
    Vanguard::Vanguard(World *owningWorld, const std::string &texturePath, const sf::Vector2f &velocity)
        : EnemySpaceship{owningWorld, texturePath},
          shooter_{new BulletShooter{this, 1.f, {50.f, 0.f}}}
    {
        SetVelocity(velocity);
        // 旋转forward方向 180°，让其逻辑面对方向为正下方
        SetActorForwardDirection(180.f);
    }

    void Vanguard::Tick(float deltaTime)
    {
        EnemySpaceship::Tick(deltaTime);
        Shoot();
    }

    void Vanguard::Shoot()
    {
        shooter_->Shoot();
    }

    Vanguard::~Vanguard()
    {
    }
}
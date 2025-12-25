#include "enemy/TwinBlade.h"
#include "weapon/BulletShooter.h"

namespace LightYears
{

    TwinBlade::TwinBlade(World *owningWorld,
                         const std::string &texturePath,
                         const sf::Vector2f &velocity)
        : EnemySpaceship{owningWorld, texturePath},
          shooterLefr_{new BulletShooter{this, 1.f, {50.f, -20.f}}},
          shooterRight_{new BulletShooter{this, 1.f, {50.f, 20.f}}}
    {
        SetVelocity(velocity);

        // 旋转forward方向 180°，让其逻辑面对方向为正下方
        SetActorForwardDirection(180.f);
    }

    void TwinBlade::Tick(float deltaTime)

    {
        EnemySpaceship::Tick(deltaTime);
        Shoot();
    }

    void TwinBlade::Shoot()
    {
        shooterLefr_->Shoot();
        shooterRight_->Shoot();
    }

    TwinBlade::~TwinBlade()
    {
    }
}
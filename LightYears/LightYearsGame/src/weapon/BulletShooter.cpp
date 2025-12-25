#include <iostream>

#include "framework/Core.h"
#include "weapon/BulletShooter.h"
#include "weapon/Bullet.h"
#include "framework/World.h"
#include "framework/MathUtility.h"

namespace LightYears
{
    BulletShooter::BulletShooter(Actor *owner,
                                 float cooldownTime,
                                 const sf::Vector2f &localPositionOffset,
                                 float localRotationOffset,
                                 const std::string &bulletTexturePath)
        : Shooter{owner},
          cooldownClock_{},
          cooldownTime_{cooldownTime},
          localPositionOffset_{localPositionOffset},
          localRotationOffset_{localRotationOffset},
          bulletTexturePath_{bulletTexturePath}
    {
    }

    bool BulletShooter::IsOnCooldown() const
    {
        if (cooldownClock_.getElapsedTime().asSeconds() > cooldownTime_ / GetCurrentLevel())
        {
            return false;
        }

        return true;
    }

    void BulletShooter::IncrementLevel(int amt)
    {
        Shooter::IncrementLevel(amt);
    }

    void BulletShooter::SetBulletTexturePath(const std::string &bulletTexturePath)
    {
        bulletTexturePath_ = bulletTexturePath;
    }

    void BulletShooter::ShootImpl()
    {
        Actor *owner = GetOwner(); // 获取发射(拥有)者指针

        sf::Vector2f ownerForwardDir = owner->GetActorForwardDirection();
        sf::Vector2f ownerRightDir = owner->GetActorRightDirection();

        cooldownClock_.restart();

        weak<Bullet> newBullet = GetOwner()->GetWorld()->SpawnActor<Bullet>(GetOwner(), bulletTexturePath_);
        newBullet.lock()->SetActorLocation(GetOwner()->GetActorLocation() + ownerForwardDir * localPositionOffset_.x + ownerRightDir * localPositionOffset_.y);
        newBullet.lock()->SetActorRotation(VectorToRotation(owner->GetActorForwardDirection()) + localRotationOffset_);

        // 获取发射者的面向逻辑方向
        //     sf::Vector2f ownerForwarDir = owner->GetActorForwardDirection();
        //     float bulletRotation = VectorToRotation(ownerForwarDir);
        //     newBullet.lock()->SetActorRotation(bulletRotation);
    }

    BulletShooter::~BulletShooter()
    {
    }
}
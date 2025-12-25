#include "weapon/Shooter.h"
#include "framework/Actor.h"

namespace LightYears
{
    Shooter::Shooter(Actor *owner)
        : owner_{owner},
          currentLevel_{1},
          maxLevel_{4}
    {
    }

    void Shooter::Shoot()
    {
        if (CanShoot() && !IsOnCooldown())
            ShootImpl();
    }

    void Shooter::IncrementLevel(int amt)
    {
        if (currentLevel_ == maxLevel_)
            return;

        ++currentLevel_;
    }

    void Shooter::SetCurrentLevel(int level)
    {
        currentLevel_ = level;
    }
}
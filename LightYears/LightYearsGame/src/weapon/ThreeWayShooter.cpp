#include "weapon/ThreeWayShooter.h"

namespace LightYears
{
    ThreeWayShooter::ThreeWayShooter(Actor *owner,
                                     float cooldownTime,
                                     const sf::Vector2f &localOffset)
        : Shooter{owner},
          shooterLeft_{owner, cooldownTime, localOffset + sf::Vector2f{10, -10}, -30.f, "SpaceShooterRedux/PNG/Lasers/laserRed01.png"},
          shooterMid_{owner, cooldownTime, localOffset + sf::Vector2f{10, 10}, 30.f, "SpaceShooterRedux/PNG/Lasers/laserRed01.png"},
          shooterRight_{owner, cooldownTime, localOffset, 0.f, "SpaceShooterRedux/PNG/Lasers/laserRed01.png"},
          topLevelShooterLeft_{owner, cooldownTime, localOffset + sf::Vector2f{10, 10}, 15.f, "SpaceShooterRedux/PNG/Lasers/laserRed01.png"},
          topLevelShooterRight_{owner, cooldownTime, localOffset + sf::Vector2f{10, -10}, -15.f, "SpaceShooterRedux/PNG/Lasers/laserRed01.png"}
    {
    }

    void ThreeWayShooter::IncrementLevel(int amt)
    {
        Shooter::IncrementLevel(amt);
        shooterLeft_.IncrementLevel(amt);
        shooterMid_.IncrementLevel(amt);
        shooterRight_.IncrementLevel(amt);

        topLevelShooterLeft_.IncrementLevel(amt);
        topLevelShooterRight_.IncrementLevel(amt);
    }

    void ThreeWayShooter::SetCurrentLevel(int level)
    {
        Shooter::SetCurrentLevel(level);
        shooterLeft_.SetCurrentLevel(level);
        shooterMid_.SetCurrentLevel(level);
        shooterRight_.SetCurrentLevel(level);

        topLevelShooterLeft_.SetCurrentLevel(level);
        topLevelShooterRight_.SetCurrentLevel(level);
    }

    void ThreeWayShooter::ShootImpl()
    {
        shooterLeft_.Shoot();
        shooterMid_.Shoot();
        shooterRight_.Shoot();

        if (GetCurrentLevel() == GetMaxLevel())
        {
            topLevelShooterLeft_.Shoot();
            topLevelShooterRight_.Shoot();
        }
    }
}

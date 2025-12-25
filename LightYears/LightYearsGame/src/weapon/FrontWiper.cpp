#include "weapon/FrontWiper.h"

namespace LightYears
{
    LightYears::FrontWiper::FrontWiper(Actor *ownerActor,
                                       float cooldownTime,
                                       const sf::Vector2f &localOffset,
                                       float width)
        : Shooter{ownerActor},
          width_{width},
          shooter1_{ownerActor, cooldownTime, {localOffset.x, localOffset.y - width / 2.f}, 0.f, "SpaceShooterRedux/PNG/Lasers/laserGreen11.png"},
          shooter2_{ownerActor, cooldownTime, {localOffset.x, localOffset.y - width / 6.f}, 0.f, "SpaceShooterRedux/PNG/Lasers/laserBlue07.png"},
          shooter3_{ownerActor, cooldownTime, {localOffset.x, localOffset.y + width / 6.f}, 0.f, "SpaceShooterRedux/PNG/Lasers/laserBlue07.png"},
          shooter4_{ownerActor, cooldownTime, {localOffset.x, localOffset.y + width / 2.f}, 0.f, "SpaceShooterRedux/PNG/Lasers/laserGreen11.png"},
          shooter5_{ownerActor, cooldownTime / 1.5f, {localOffset.x, localOffset.y + width / 1.5f}, 15.f, "SpaceShooterRedux/PNG/Lasers/laserGreen11.png"},
          shooter6_{ownerActor, cooldownTime / 1.5f, {localOffset.x, localOffset.y - width / 1.5f}, -15.f, "SpaceShooterRedux/PNG/Lasers/laserGreen11.png"}
    {
    }

    void FrontWiper::IncrementLevel(int amt)
    {
        Shooter::IncrementLevel(amt);

        shooter1_.IncrementLevel(amt);
        shooter2_.IncrementLevel(amt);
        shooter3_.IncrementLevel(amt);
        shooter4_.IncrementLevel(amt);
        shooter5_.IncrementLevel(amt);
        shooter6_.IncrementLevel(amt);
    }

    void FrontWiper::SetCurrentLevel(int level)
    {
        Shooter::SetCurrentLevel(level);

        shooter1_.SetCurrentLevel(level);
        shooter2_.SetCurrentLevel(level);
        shooter3_.SetCurrentLevel(level);
        shooter4_.SetCurrentLevel(level);
        shooter5_.SetCurrentLevel(level);
        shooter6_.SetCurrentLevel(level);
    }

    void FrontWiper::ShootImpl()
    {
        shooter1_.Shoot();
        shooter2_.Shoot();
        shooter3_.Shoot();
        shooter4_.Shoot();

        if (GetCurrentLevel() == GetMaxLevel())
        {
            shooter5_.Shoot();
            shooter6_.Shoot();
        }
    }
}

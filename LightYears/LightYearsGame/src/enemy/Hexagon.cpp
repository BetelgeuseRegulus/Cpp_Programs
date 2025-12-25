#include "Enemy/Hexagon.h"
#include "weapon/BulletShooter.h"

namespace LightYears
{

    LightYears::Hexagon::Hexagon(World *owningWorld, const std::string &texturePath, const sf::Vector2f &velocity)
        : EnemySpaceship(owningWorld, texturePath),
          shooter1_{new BulletShooter{this, 1.f, sf::Vector2f{30.f, 60.f}, 60.f}},
          shooter2_{new BulletShooter{this, 1.f, sf::Vector2f{30.f, -60.f}, -60.f}},
          shooter3_{new BulletShooter{this, 1.f, sf::Vector2f{60.f, 0.f}}},
          shooter4_{new BulletShooter{this, 1.f, sf::Vector2f{-60.f, 0.f}, -180.f}},
          shooter5_{new BulletShooter{this, 1.f, sf::Vector2f{-30.f, 60.f}, 120.f}},
          shooter6_{new BulletShooter{this, 1.f, sf::Vector2f{-30.f, -60.f}, -120.f}}
    {
        SetVelocity(velocity);
    }

    void Hexagon::Tick(float deltaTime)
    {
        EnemySpaceship::Tick(deltaTime);
        Shoot();
    }

    void Hexagon::Shoot()
    {
        shooter1_->Shoot();
        shooter2_->Shoot();
        shooter3_->Shoot();
        shooter4_->Shoot();
        shooter5_->Shoot();
        shooter6_->Shoot();
    }

    Hexagon::~Hexagon()
    {
    }
}
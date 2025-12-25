#include "Enemy/UFO.h"
#include "weapon/BulletShooter.h"

namespace LightYears
{

    LightYears::UFO::UFO(World *owningWorld,
                         const sf::Vector2f &velocity,
                         const std::string texturePath,
                         float rotationSpeed)
        : EnemySpaceship{owningWorld, texturePath},
          shooter1_{new BulletShooter{this, .5f, sf::Vector2f{0.f, 0.f}, -60}},
          shooter2_{new BulletShooter{this, .5f, sf::Vector2f{0.f, 0.f}, 60}},
          shooter3_{new BulletShooter{this, .5f, sf::Vector2f{0.f, 0.f}, 180.f}},
          rotationSpeed_{rotationSpeed}
    {
        SetVelocity(velocity);
    }

    UFO::~UFO()
    {
    }

    void UFO::Tick(float deltaTime)
    {
        EnemySpaceship::Tick(deltaTime);
        Shoot();
        AddActorRotationOffset(rotationSpeed_ * deltaTime);
    }

    void UFO::Shoot()
    {
        shooter1_->Shoot();
        shooter2_->Shoot();
        shooter3_->Shoot();
    }
}
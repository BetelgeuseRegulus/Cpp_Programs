#include "weapon/Bullet.h"

namespace LightYears
{
    Bullet::Bullet(World *world, Actor *owner, const std::string &texturePath, float speed, float damage)
        : Actor{world, texturePath},
          owner_{owner},
          speed_{speed},
          damage_{damage}
    {
        SetTeamID(owner->GetTeamID());
    }

    void Bullet::Tick(float deltaTime)
    {
        Actor::Tick(deltaTime);
        Move(deltaTime);

        if (IsActorOutOfWindowBounds())
        {
            Destroy();
        }
    }

    void Bullet::BeginPlay()
    {
        Actor::BeginPlay();
        SetEnablePhysics(true);
    }

    void Bullet::Move(float deltaTime)
    {
        AddActorLocationOffset(GetActorForwardDirection() * speed_ * deltaTime);
    }

    void Bullet::SetSpeed(float newSpeed)
    {
        speed_ = newSpeed;
    }

    void Bullet::SetDamage(float newDamage)
    {
        damage_ = newDamage;
    }

    void Bullet::OnActorBeginOverlap(Actor *other)
    {
        if (IsOtherHostile(other))
        {
            other->ApplyDamage(GetDamage());
            Destroy();
        }
    }
} // namespace LightYears

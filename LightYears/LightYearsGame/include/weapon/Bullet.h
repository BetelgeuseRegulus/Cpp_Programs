#pragma once

#include "framework/Actor.h"

namespace LightYears
{
    class Bullet : public Actor
    {
    public:
        Bullet(World *world, Actor *owner, const std::string &texture, float speed = 600.f, float damage = 10);

        void SetSpeed(float newSpeed);

        void SetDamage(float newDamage);
        float GetDamage() const { return damage_; }

        virtual void Tick(float deltaTime) override;
        virtual void BeginPlay() override;

    private:
        void Move(float deltaTime);
        virtual void OnActorBeginOverlap(Actor *other) override;

    private:
        Actor *owner_{};
        float speed_{};
        float damage_{};
    };
} // namespace LightYears

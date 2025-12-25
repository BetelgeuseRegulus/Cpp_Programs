#pragma once
#include "framework/Actor.h"
#include "gameplay/HealthComponent.h"

namespace LightYears
{
    class Spaceship : public Actor
    {
    public:
        Spaceship(World *owningWord, const std::string &texturePath = "");
        virtual void Tick(float deltaTime) override;

        void SetVelocity(const sf::Vector2f &newVel);
        sf::Vector2f GetVelocity() const { return velocity_; }

        virtual void Shoot();
        virtual void BeginPlay() override;
        virtual void ApplyDamage(float amt) override;

        HealthComponent &GetHealthComp() { return healthComp_; }

    private:
        void Blink();
        void UpdateBlink(float deltaTime);

        virtual void OnHealthChanged(float amt, float health, float maxHealth);
        virtual void OnTakeDamage(float amt, float health, float maxHealth);
        virtual void Blow();
        virtual void Blew();

    private:
        sf::Vector2f velocity_{};
        HealthComponent healthComp_;

        float blinkTime_;
        float blinkDuration_;
        sf::Color blinkColorOffset_;
    };
}
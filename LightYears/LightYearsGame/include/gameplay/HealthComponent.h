#pragma once
#include "framework/Delegate.h"

namespace LightYears
{
    class HealthComponent
    {
    public:
        HealthComponent(float health, float maxHealth);
        ~HealthComponent();

        void ChangeHealth(float amt);

        float GetHealth() const { return health_; }
        float GetMaxHealth() const { return maxHealth_; }

        void SetInitialHealth(float health, float maxHealth);

    public:
        Delegate<float, float, float> onHealthChanged_;
        Delegate<float, float, float> onTakenDamage_;
        Delegate<> onHealthEmpty_;

    private:
        void TakenDamage(float amt);
        void HealthEmpty();
        void HealthRegen(float amt);

    private:
        float health_{};
        float maxHealth_{};
    };
}
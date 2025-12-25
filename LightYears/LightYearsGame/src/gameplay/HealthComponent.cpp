
#include "gamePlay/HealthComponent.h"
#include "framework/Core.h"

namespace LightYears
{
    HealthComponent::HealthComponent(float health, float maxHealth)
        : health_{health},
          maxHealth_{maxHealth}
    {
    }
    HealthComponent::~HealthComponent()
    {
    }

    /**
     * @brief
     *
     * @param amt  amount (变化)数量
     */
    void HealthComponent::ChangeHealth(float amt)
    {
        if (amt == 0)
            return;
        if (health_ == 0)
            return;

        health_ += amt;
        if (health_ < 0)
        {
            health_ = 0;
        }

        if (health_ > maxHealth_)
        {
            health_ = maxHealth_;
        }

        onHealthChanged_.Broadcast(amt, health_, maxHealth_);

        if (amt < 0)
        {
            TakenDamage(-amt);
            if (health_ <= 0)
            {
                HealthEmpty();
            }
        }
    }

    void HealthComponent::TakenDamage(float amt)
    {
        onTakenDamage_.Broadcast(amt, health_, maxHealth_);
    }

    void HealthComponent::HealthEmpty()
    {
        onHealthEmpty_.Broadcast();
    }

    void HealthComponent::HealthRegen(float amt)
    {
    }

    void HealthComponent::SetInitialHealth(float health, float maxHealth)
    {
        health_ = health;
        maxHealth_ = maxHealth;
    }

} // namespace LightYears

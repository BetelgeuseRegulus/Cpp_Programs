#include "spaceship/Spaceship.h"
#include "framework/MathUtility.h"
#include "VFX/Explosion.h"

namespace LightYears
{
    Spaceship::Spaceship(World *owningWord, const std::string &texturePath)
        : Actor{owningWord, texturePath},
          velocity_{},
          healthComp_{100.f, 100.f},
          blinkTime_{0.f},
          blinkDuration_{0.2f},
          blinkColorOffset_{255, 0, 0, 255}
    {
    }

    void Spaceship::Tick(float deltaTime)
    {
        Actor::Tick(deltaTime);
        AddActorLocationOffset(GetVelocity() * deltaTime);

        UpdateBlink(deltaTime);
    }

    void Spaceship::SetVelocity(const sf::Vector2f &newVel)
    {
        velocity_ = newVel;
    }

    void Spaceship::Shoot()
    {
    }

    void Spaceship::BeginPlay()
    {
        Actor::BeginPlay();

        SetEnablePhysics(true); // 启用物理碰撞检测

        healthComp_.onHealthChanged_.BindAction(GetWeakRef(), &Spaceship::OnHealthChanged);
        healthComp_.onTakenDamage_.BindAction(GetWeakRef(), &Spaceship::OnTakeDamage);
        healthComp_.onHealthEmpty_.BindAction(GetWeakRef(), &Spaceship::Blow);
    }

    void Spaceship::ApplyDamage(float amt)
    {
        healthComp_.ChangeHealth(-amt);
    }

    void Spaceship::Blink()
    {
        if (blinkTime_ == 0.f)
        {
            blinkTime_ = blinkDuration_;
        }
    }

    void Spaceship::UpdateBlink(float deltaTime)
    {
        if (blinkTime_ > 0)
        {
            blinkTime_ -= deltaTime;
            blinkTime_ = blinkTime_ > 0 ? blinkTime_ : 0.f;

            GetSprite().setColor(LerpColor(sf::Color::White, blinkColorOffset_, blinkTime_));
        }
    }

    void Spaceship::OnHealthChanged(float amt, float health, float maxHealth)
    {
    }

    void Spaceship::OnTakeDamage(float amt, float health, float maxHealth)
    {
        Blink();
    }

    /**
     * @brief 飞船爆炸处理
     *
     *  负责执行飞船被击中摧毁时的动画表现和释放资源
     */
    void Spaceship::Blow()
    {
        Explosion *exp = new Explosion();
        exp->SpawnExplosion(GetWorld(), GetActorLocation());
        Blew();
        Destroy();
        delete exp;
    }

    void Spaceship::Blew()
    {
    }
}
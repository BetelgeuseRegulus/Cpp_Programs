#include "Enemy/Boss.h"

namespace LightYears
{
    Boss::Boss(World *world)
        : EnemySpaceship{world, "SpaceShooterRedux/PNG/Enemies/boss.png"},
          speed_{100.f},
          baseSpeed_{100.f},
          switchDistanceToEdge_{100.f},
          baseShooterLeft_{this, 1.f, {50.f, -50.f}},
          baseShooterRight_{this, 1.f, {50.f, 50.f}},
          threeWayShooter_{this, 4.f, {100.f, 0.f}},
          frontalWiperLeft_{this, 5.f, {80.f, -100}},
          frontalWiperRight_{this, 5.f, {80.f, 100}},
          finalStageShooterLeft_{this, 0.4f, {50, -150.f}},
          finalStageShooterRight_{this, 0.4f, {50, 150.f}},
          stage_{1}
    {
        SetActorRotation(180.f);
        SetVelocity({speed_, 0.f});
        SetRewardSpawnWeight(0.f);
        // BeginPlay();
    }

    void Boss::Tick(float deltaTime)
    {
        EnemySpaceship::Tick(deltaTime);
        ShootBaseShooters();
        ShootFrontalWipers();
        ShootThreeWayShooter();

        if (stage_ == 4)
        {
            finalStageShooterLeft_.Shoot();
            finalStageShooterRight_.Shoot();
        }
        CheckMove();
    }

    void Boss::BeginPlay()
    {
        EnemySpaceship::BeginPlay();

        HealthComponent &healthComp = GetHealthComp();
        healthComp.SetInitialHealth(3000.f, 3000.f);
        healthComp.onHealthChanged_.BindAction(GetWeakRef(), &Boss::HealthChanged);
    }

    void Boss::CheckMove()
    {
        if (GetActorLocation().x > GetWindowSize().x - switchDistanceToEdge_)
        {
            SetVelocity({-speed_, 0.f});
        }
        else if (GetActorLocation().x < switchDistanceToEdge_)
        {
            SetVelocity({speed_, 0.f});
        }
    }

    void Boss::ShootBaseShooters()
    {
        baseShooterLeft_.Shoot();
        baseShooterRight_.Shoot();
    }

    void Boss::ShootThreeWayShooter()
    {
        threeWayShooter_.Shoot();
    }

    void Boss::ShootFrontalWipers()
    {
        frontalWiperLeft_.Shoot();
        frontalWiperRight_.Shoot();
    }

    void Boss::HealthChanged(float amt, float currentHealth, float maxHealth)
    {
        float percentLeft = currentHealth / maxHealth;
        if (percentLeft < 0.7 && percentLeft > 0.5)
        {
            SetStage(2);
        }

        if (percentLeft < 0.5 && percentLeft > 0.3)
        {
            SetStage(3);
        }

        if (percentLeft < 0.3)
        {
            SetStage(4);
        }
    }

    void Boss::SetStage(int newStage)
    {
        stage_ = newStage;
        baseShooterLeft_.SetCurrentLevel(stage_);
        baseShooterRight_.SetCurrentLevel(stage_);
        frontalWiperLeft_.SetCurrentLevel(stage_);
        frontalWiperRight_.SetCurrentLevel(stage_);
        threeWayShooter_.SetCurrentLevel(stage_);
        speed_ = baseSpeed_ * stage_;
    }
}
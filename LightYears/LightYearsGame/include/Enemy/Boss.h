#pragma once

#include "Enemy/EnemySpaceship.h"
#include "weapon/BulletShooter.h"
#include "weapon/ThreeWayShooter.h"
#include "weapon/FrontWiper.h"

namespace LightYears
{
    class Boss : public EnemySpaceship
    {
    public:
        Boss(World *World);
        ~Boss() = default;
        virtual void Tick(float deltaTime) override;
        virtual void BeginPlay() override;

    private:
        void CheckMove();
        void ShootBaseShooters();

        void ShootThreeWayShooter();
        void ShootFrontalWipers();

        void HealthChanged(float amt, float currentHealth, float maxHealth);
        void SetStage(int newStage);

    private:
        float speed_{};
        float baseSpeed_;
        float switchDistanceToEdge_{};

        BulletShooter baseShooterLeft_;
        BulletShooter baseShooterRight_;

        ThreeWayShooter threeWayShooter_;

        FrontWiper frontalWiperLeft_;
        FrontWiper frontalWiperRight_;

        BulletShooter finalStageShooterLeft_;
        BulletShooter finalStageShooterRight_;

        int stage_{};
    };
}
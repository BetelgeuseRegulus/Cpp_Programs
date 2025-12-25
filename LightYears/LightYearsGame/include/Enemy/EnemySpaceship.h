#pragma once

#include "spaceship/Spaceship.h"
#include "player/Reward.h"

namespace LightYears
{
    class EnemySpaceship : public Spaceship
    {
    public:
        EnemySpaceship(World *owningWorld,
                       const std::string &texturePath,
                       float collisionDamage = 200.f,
                       float rewardSpawnWeight = 0.5f,
                       const List<RewardFactoryFunc> rewards = {CreateHealthReward,
                                                                CreateThreeWayShooterReward,
                                                                CreateFrontalWiperReward,
                                                                CreateLifeReward});

        virtual void Tick(float deltaTime) override;

        void SetScoreAwardAmt(unsigned int amt);
        void SetRewardSpawnWeight(float weight);

    private:
        virtual void OnActorBeginOverlap(Actor *other) override;
        virtual void Blew() override;

        void SpawnReward();

    private:
        float collisionDamage_{};

        List<RewardFactoryFunc> rewardFactories_;

        unsigned int scoreAwardAmt_{};
        float rewardSpawnWeight_{};
    };
}
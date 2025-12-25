#pragma once

#include <functional>
#include "framework/Actor.h"

namespace LightYears
{
    class PlayerSpaceship;
    class Reward;
    using RewardFunc = std::function<void(PlayerSpaceship *)>;
    using RewardFactoryFunc = std::function<weak<Reward>(World *)>;
    class Reward : public Actor
    {
    public:
        Reward(World *world, const std::string &texturePath, RewardFunc rewardRunc, float speed = 200.f);
        ~Reward();

        virtual void BeginPlay() override;
        virtual void Tick(float deltaTime) override;

    private:
        virtual void OnActorBeginOverlap(Actor *otherActor) override;

    private:
        float speed_{};
        RewardFunc rewardFunc_{};
    };
    weak<Reward> CreateHealthReward(World *world);
    weak<Reward> CreateThreeWayShooterReward(World *world);
    weak<Reward> CreateFrontalWiperReward(World *world);
    weak<Reward> CreateLifeReward(World *world);

    weak<Reward> CreateReward(World *world, const std::string &texturePath, RewardFunc rewardFunc);

    void RewardHealth(PlayerSpaceship *player);
    void RewardThreewayShooter(PlayerSpaceship *player);
    void RewardFrontalWiper(PlayerSpaceship *plaper);
    void RewardLife(PlayerSpaceship *player);
}
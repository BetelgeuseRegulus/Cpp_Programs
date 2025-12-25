#pragma once

#include <SFML/Graphics.hpp>
#include "gameplay/GameStage.h"
#include "framework/TimerManager.h"

namespace LightYears
{
    class ChaosStage : public GameStage
    {
    public:
        ChaosStage(World *world);

        virtual void StartStage() override;

    private:
        virtual void StageFinished() override;
        void SpawnVanguard();
        void SpawnTwinBlade();
        void SpawnHexagon();
        void SpawnUFO();

        void IncreaseDifficulity();
        void StageDurationReached();

        sf::Vector2f GetRandomSpawnLocationTop() const;
        sf::Vector2f GetRandomSpawnLocationSide() const;

    private:
        float spawnInterval_;
        float minSpawnInterval_;

        float spawnIntervalDecrement_;
        float spawnIntervalDecrementInterval_;

        float stageDuration_;

        TimerHandle difficultTimerHandle_;
        TimerHandle spawnTimer_;
    };
}
#pragma once
#include <SFML/Graphics.hpp>

#include "gameplay/GameStage.h"
#include "framework/TimerManager.h"

namespace LightYears
{
    class UFOStage : public GameStage
    {
    public:
        UFOStage(World *world);

        virtual void StartStage() override;

    private:
        virtual void StageFinished() override;

        sf::Vector2f GetRandomSpawnLoc() const;
        void SpawnUFO();

    private:
        float spawnInterval_;
        int spawnAmt_;
        int currentSpawnAmt_;
        float UFOspeed_;

        TimerHandle spawnTimer_;
    };
} // namespace LightYears

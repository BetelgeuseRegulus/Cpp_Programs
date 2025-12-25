#pragma once
#include <SFML/Graphics.hpp>
#include "framework/TimerManager.h"
#include "gameplay/GameStage.h"

namespace LightYears
{
    class TwinBladeStage : public GameStage
    {
    public:
        TwinBladeStage(World *world);
        virtual void StartStage() override;

    private:
        void SpawnTwinBlade();
        virtual void StageFinished() override;

    private:
        float spawnInterval_{};
        float spawnDistanceToCenter_{};

        sf::Vector2f leftSpawnLoc_{};
        sf::Vector2f rightSpawnLoc_{};
        sf::Vector2f spawnLoc_{};

        int spawnAmt_{};
        int currentSpawnCount_{};

        TimerHandle spawnTimerHandle_{};
    };
}
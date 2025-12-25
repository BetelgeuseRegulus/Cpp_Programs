#pragma once
#include <SFML/Graphics.hpp>

#include "gameplay/GameStage.h"
#include "framework/TimerManager.h"

namespace LightYears
{
    class HexagonStage : public GameStage
    {
    public:
        HexagonStage(World *world);
        virtual void StartStage() override;

    private:
        virtual void StageFinished() override;
        void SpawnHexagon();

    private:
        float spawnInterval_;
        float sideSpawnOffset_;

        int spawnGroupAmt_;
        int currentSpawnCount_;

        sf::Vector2f midSpawnLoc_{};
        sf::Vector2f leftSpawnLoc_{};
        sf::Vector2f rightSpawnLoc_{};

        TimerHandle spawnTimer_;
    };
} // namespace LightYears

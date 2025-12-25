#include "enemy/UFOStage.h"
#include "enemy/UFO.h"
#include "framework/World.h"
#include "framework/MathUtility.h"

namespace LightYears
{
    UFOStage::UFOStage(World *world)
        : GameStage{world},
          spawnInterval_{4.f},
          spawnAmt_{10},
          currentSpawnAmt_{0},
          UFOspeed_{200.f}
    {
    }

    void UFOStage::StartStage()
    {
        spawnTimer_ = TimerManager::Get().SetTimer(GetWeakRef(), &UFOStage::SpawnUFO, spawnInterval_, true);
    }

    void UFOStage::StageFinished()
    {
        TimerManager::Get().ClearTimer(spawnTimer_);
    }

    sf::Vector2f UFOStage::GetRandomSpawnLoc() const
    {
        auto windowSize = GetWorld()->GetWindowSize();
        float spawnLeft = RandomRange(-1, 1);
        float spawnLocX = 0;

        if (spawnLeft < 0)
        {
            spawnLocX = windowSize.x + 100.f; // 生成在右侧屏幕
        }
        else
        {
            spawnLocX = -100.f; // 生成在左侧屏幕
        }

        float spawnLocY = RandomRange(0, windowSize.y);
        return sf::Vector2f{spawnLocX, spawnLocY};
    }

    void UFOStage::SpawnUFO()
    {
        sf::Vector2f spawnLoc = GetRandomSpawnLoc();
        auto windowSize = GetWorld()->GetWindowSize();
        sf::Vector2f center{windowSize.x / 2.f, windowSize.y / 2.f};
        sf::Vector2f spawnLocToCenter{center.x - spawnLoc.x, center.y - spawnLoc.y};
        Normalize(spawnLocToCenter);

        sf::Vector2f spawnVelocity = spawnLocToCenter * UFOspeed_;

        weak<UFO> newUFO = GetWorld()->SpawnActor<UFO>(spawnVelocity);
        newUFO.lock()->SetActorLocation(spawnLoc);

        if (++currentSpawnAmt_ == spawnAmt_)
        {
            FinishStage();
        }
    }
}

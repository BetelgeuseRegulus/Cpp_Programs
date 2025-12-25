#include "enemy/HexagonStage.h"
#include "enemy/Hexagon.h"
#include "framework/World.h"

namespace LightYears
{
    HexagonStage::HexagonStage(World *world)
        : GameStage{world},
          spawnInterval_{5.f},
          sideSpawnOffset_{80.f},
          spawnGroupAmt_{5},
          currentSpawnCount_{0},
          midSpawnLoc_{world->GetWindowSize().x / 2.f, -100.f},
          rightSpawnLoc_{world->GetWindowSize().x / 2.f + sideSpawnOffset_, -100.f - sideSpawnOffset_},
          leftSpawnLoc_{world->GetWindowSize().x / 2.f - sideSpawnOffset_, -100.f - sideSpawnOffset_}
    {
    }
    void HexagonStage::StartStage()
    {
        spawnTimer_ = TimerManager::Get().SetTimer(GetWeakRef(), &HexagonStage::SpawnHexagon, spawnInterval_, true);
    }

    void HexagonStage::StageFinished()
    {
        TimerManager::Get().ClearTimer(spawnTimer_);
    }

    void HexagonStage::SpawnHexagon()
    {
        weak<Hexagon> newHexagon = GetWorld()->SpawnActor<Hexagon>();
        newHexagon.lock()->SetActorLocation(midSpawnLoc_);

        newHexagon = GetWorld()->SpawnActor<Hexagon>();
        newHexagon.lock()->SetActorLocation(leftSpawnLoc_);

        newHexagon = GetWorld()->SpawnActor<Hexagon>();
        newHexagon.lock()->SetActorLocation(rightSpawnLoc_);

        if (++currentSpawnCount_ == spawnGroupAmt_)
        {
            FinishStage();
        }
    }
}
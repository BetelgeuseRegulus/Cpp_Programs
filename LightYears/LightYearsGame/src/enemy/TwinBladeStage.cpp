#include "Enemy/TwinBladeStage.h"
#include "framework/World.h"
#include "enemy/TwinBlade.h"

namespace LightYears
{
    TwinBladeStage::TwinBladeStage(World *world)
        : GameStage(world),
          spawnInterval_{1.5f},
          spawnDistanceToCenter_{100.f},
          leftSpawnLoc_{world->GetWindowSize().x / 2.f - spawnDistanceToCenter_, -100.f},
          rightSpawnLoc_{world->GetWindowSize().x / 2.f + spawnDistanceToCenter_, -100.f},
          spawnLoc_{leftSpawnLoc_},
          spawnAmt_{10},
          currentSpawnCount_{0}
    {
    }

    void TwinBladeStage::StartStage()
    {
        spawnTimerHandle_ = TimerManager::Get().SetTimer(GetWeakRef(), &TwinBladeStage::SpawnTwinBlade, spawnInterval_, true);
    }

    void TwinBladeStage::SpawnTwinBlade()
    {
        weak<TwinBlade> newTwinBlade = GetWorld()->SpawnActor<TwinBlade>();
        newTwinBlade.lock()->SetActorLocation(spawnLoc_);

        if (spawnLoc_ == leftSpawnLoc_)
        {
            spawnLoc_ = rightSpawnLoc_;
        }
        else
        {
            spawnLoc_ = leftSpawnLoc_;
        }

        ++currentSpawnCount_;
        if (currentSpawnCount_ == spawnAmt_)
        {
            FinishStage();
        }
    }

    void TwinBladeStage::StageFinished()
    {
        TimerManager::Get().ClearTimer(spawnTimerHandle_);
    }
}

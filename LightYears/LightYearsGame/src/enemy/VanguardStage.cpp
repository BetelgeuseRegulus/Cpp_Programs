#include "enemy/VanguardStage.h"
#include "enemy/Vanguard.h"
#include "framework/World.h"

namespace LightYears
{
    VanguardStage::VanguardStage(World *world)
        : GameStage(world),
          spawnInterval_{2.f},
          switchInterval_{5.f},
          spawnDistanceToEdge_{100.f},
          leftSpawnLoc_{0.0f, 0.0f},
          rightSpwanLoc_{0.0f, 0.0f},
          spawnLoc_{0.0f, 0.0f},
          rowsToSpawn_{3},
          rowsSpawnCount_{0},
          vangaurdsPerRow_{5},
          currentRowVanguardCount_{0}
    {
    }

    void VanguardStage::StartStage()
    {
        auto windowSize = GetWorld()->GetWindowSize();
        leftSpawnLoc_ = sf::Vector2f{spawnDistanceToEdge_, -100.f};
        rightSpwanLoc_ = sf::Vector2f{windowSize.x - spawnDistanceToEdge_, -100.f};

        SwitchRow();
    }

    void VanguardStage::StageFinished()
    {
        TimerManager::Get().ClearTimer(spawnTimerHandle_);
        TimerManager::Get().ClearTimer(switchTimerHandle_);
    }

    void VanguardStage::SpawnVanguard()
    {
        weak<Vanguard> newVanguard = GetWorld()->SpawnActor<Vanguard>();
        newVanguard.lock()->SetActorLocation(spawnLoc_);

        ++currentRowVanguardCount_;
        if (currentRowVanguardCount_ == vangaurdsPerRow_)
        {
            TimerManager::Get().ClearTimer(spawnTimerHandle_);
            switchTimerHandle_ = TimerManager::Get().SetTimer(GetWeakRef(), &VanguardStage::SwitchRow, switchInterval_, false);
            currentRowVanguardCount_ = 0;
        }
    }

    void VanguardStage::SwitchRow()
    {

        if (rowsSpawnCount_ == rowsToSpawn_)
        {
            FinishStage();
            return;
        }

        if (spawnLoc_ == leftSpawnLoc_)
        {
            spawnLoc_ = rightSpwanLoc_;
        }
        else
        {
            spawnLoc_ = leftSpawnLoc_;
        }
        spawnTimerHandle_ = TimerManager::Get().SetTimer(GetWeakRef(), &VanguardStage::SpawnVanguard, spawnInterval_, true);
        ++rowsSpawnCount_;
    }
}

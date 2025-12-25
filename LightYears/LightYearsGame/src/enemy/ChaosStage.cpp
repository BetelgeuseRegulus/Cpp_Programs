#include "enemy/ChaosStage.h"
#include "enemy/Vanguard.h"
#include "enemy/TwinBlade.h"
#include "enemy/Hexagon.h"
#include "enemy/UFO.h"
#include "framework/TimerManager.h"
#include "framework/World.h"
#include "framework/MathUtility.h"

namespace LightYears
{
    LightYears::ChaosStage::ChaosStage(World *world)
        : GameStage{world},
          spawnInterval_{4.f},
          minSpawnInterval_{0.4f},
          spawnIntervalDecrement_{0.5f},
          spawnIntervalDecrementInterval_{5.f},
          stageDuration_{90.f}
    {
    }

    void ChaosStage::StartStage()
    {
        spawnTimer_ = TimerManager ::Get().SetTimer(GetWeakRef(), &ChaosStage::SpawnVanguard, spawnInterval_);
        difficultTimerHandle_ = TimerManager::Get().SetTimer(GetWeakRef(), &ChaosStage::IncreaseDifficulity, spawnIntervalDecrementInterval_);
        TimerManager::Get().SetTimer(GetWeakRef(), &ChaosStage::StageDurationReached, stageDuration_);
    }

    void ChaosStage::StageFinished()
    {
        TimerManager::Get().ClearTimer(difficultTimerHandle_);
        TimerManager::Get().ClearTimer(spawnTimer_);
    }

    void ChaosStage::SpawnVanguard()
    {
        weak<Vanguard> newVanguard = GetWorld()->SpawnActor<Vanguard>();
        newVanguard.lock()->SetActorLocation(GetRandomSpawnLocationTop());
        spawnTimer_ = TimerManager::Get().SetTimer(GetWeakRef(), &ChaosStage::SpawnTwinBlade, spawnInterval_);
    }

    void ChaosStage::SpawnTwinBlade()
    {
        weak<TwinBlade> newTwinBlade = GetWorld()->SpawnActor<TwinBlade>();
        newTwinBlade.lock()->SetActorLocation(GetRandomSpawnLocationTop());
        spawnTimer_ = TimerManager::Get().SetTimer(GetWeakRef(), &ChaosStage::SpawnHexagon, spawnInterval_);
    }

    void ChaosStage::SpawnHexagon()
    {
        weak<Hexagon> newHexagon = GetWorld()->SpawnActor<Hexagon>();
        newHexagon.lock()->SetActorLocation(GetRandomSpawnLocationTop());
        spawnTimer_ = TimerManager::Get().SetTimer(GetWeakRef(), &ChaosStage::SpawnUFO, spawnInterval_);
    }

    void ChaosStage::SpawnUFO()
    {
        // 在游戏场景的边缘随机位置生成一个 UFO
        sf::Vector2f spawnLoc = GetRandomSpawnLocationSide();

        // 计算朝向屏幕中心的移动方向, 让 UFO 会向屏幕中心移动
        auto windowSize = GetWorld()->GetWindowSize();
        sf::Vector2f center = sf::Vector2f{windowSize.x / 2.f, windowSize.y / 2.f};
        sf::Vector2f dirToCenter = center - spawnLoc;
        Normalize(dirToCenter);

        weak<UFO> newUFO = GetWorld()->SpawnActor<UFO>(dirToCenter * 200.f);
        newUFO.lock()->SetActorLocation(spawnLoc);

        spawnTimer_ = TimerManager::Get().SetTimer(GetWeakRef(), &ChaosStage::SpawnVanguard, spawnInterval_);
    }

    void ChaosStage::IncreaseDifficulity()
    {
        spawnInterval_ -= spawnIntervalDecrement_;
        if (spawnInterval_ < minSpawnInterval_)
        {
            spawnInterval_ = minSpawnInterval_;
        }
    }

    void ChaosStage::StageDurationReached()
    {
        FinishStage();
    }

    /**
     * @brief 获得一个随机窗口顶部位置
     *
     * @return sf::Vector2f
     */
    sf::Vector2f ChaosStage::GetRandomSpawnLocationTop() const
    {
        auto windowSize = GetWorld()->GetWindowSize();
        float spawnX = RandomRange(100.f, windowSize.x - 100.f);
        float spawnY = -100.f;

        return {spawnX, spawnY};
    }

    /**
     * @brief 获取一个屏幕两边边缘的随机位置
     *
     * @return sf::Vector2f
     */
    sf::Vector2f ChaosStage::GetRandomSpawnLocationSide() const
    {
        auto windowSize = GetWorld()->GetWindowSize();
        float spawnLeft = RandomRange(-1, 1);
        float spawnLocX = 0;

        if (spawnLeft < 0)
        {
            spawnLocX = windowSize.x + 100.f;
        }
        else
        {
            spawnLocX = -100.f;
        }

        float spawnLocY = RandomRange(0, windowSize.y);

        return sf::Vector2f{spawnLocX, spawnLocY};
    }
}
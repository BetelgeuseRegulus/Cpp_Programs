#include "gameplay/GameStage.h"
#include "framework/World.h"

namespace LightYears
{
    GameStage::GameStage(World *world)
        : world_{world},
          stageFinished_{false}
    {
    }

    GameStage::~GameStage()
    {
    }

    void GameStage::StartStage()
    {
        LOG("Stage Started");
    }

    void GameStage::TickStage(float deltaTime)
    {
    }

    void GameStage::FinishStage()
    {
        if (!IsStageValid())
            return;

        stageFinished_ = true;
        OnStageFinished_.Broadcast();
        StageFinished();
    }

    void GameStage::StageFinished()
    {
    }

    bool GameStage::IsStageValid()
    {
        return !IsPendingDestory() && world_ && !world_->IsPendingDestory();
    }
}

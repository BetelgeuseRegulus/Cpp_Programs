#pragma once

#include "framework/Object.h"
#include "framework/Delegate.h"

namespace LightYears
{
    class World;
    class GameStage : public Object
    {
    public:
        GameStage(World *world);
        ~GameStage();

        const World *GetWorld() const { return world_; }
        World *GetWorld() { return world_; }

        void FinishStage();
        bool IsStageFinished() const { return stageFinished_; }

        virtual void StartStage();
        virtual void TickStage(float deltaTime);

    public:
        Delegate<> OnStageFinished_;

    private:
        virtual void StageFinished();

#pragma region custom
        bool IsStageValid();
#pragma endregion

    private:
        World *world_{};
        bool stageFinished_{};
    };
}
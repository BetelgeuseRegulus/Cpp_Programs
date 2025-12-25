#pragma once
#include "framework/World.h"
#include "framework/Core.h"
#include "framework/TimerManager.h"
#include "Level/GameLevelOne.h"

namespace LightYears
{
    class PlayerSpaceship;
    class GameplayHUD;
    class GameLevelOne : public World
    {
    public:
        GameLevelOne(Application *owningApp);

    private:
        virtual void AllGameStageFinished() override;
        virtual void BeginPlay() override;
        virtual void Tick(float DeltaTime) override;

        virtual void InitGameStages() override;

        void PlayerSpaceshipDestoryed(Actor *destoryedPlayerSpaceship);
        void GameOver();

        void Restart();
        void QuitGame();

        void SpwanCosmetics(); // 生成装饰元素

    private:
        weak<PlayerSpaceship> playerSpaceship_;
        weak<GameplayHUD> gameplayHUD_;

        TimerHandle timerHandle_Test;
    };
}
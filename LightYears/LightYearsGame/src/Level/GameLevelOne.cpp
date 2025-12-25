#include "Level/GameLevelOne.h"
#include "enemy/ChaosStage.h"
#include "enemy/HexagonStage.h"
#include "enemy/TwinBladeStage.h"
#include "enemy/VanguardStage.h"
#include "enemy/BossStage.h"
#include "enemy/UFOStage.h"
#include "framework/Actor.h"
#include "framework/BackdropActor.h"
#include "framework/AssetManager.h"
#include "framework/TimerManager.h"
#include "framework/World.h"
#include "framework/BackgroundLayer.h"
#include "gameFramework/GameApplication.h"
#include "gameplay/GameStage.h"
#include "gameplay/WaitStage.h"
#include "player/PlayerSpaceship.h"
#include "player/PlayerManager.h"
#include "widgets/GameplayHUD.h"

namespace LightYears
{
    GameLevelOne::GameLevelOne(Application *owningApp)
        : World{owningApp}
    {
        // Actor的默认方向是正上方
    }

    void GameLevelOne::BeginPlay()
    {

        SpwanCosmetics();

        Player &newPlayer = PlayerManager::Get().CreateNewPlayer();
        playerSpaceship_ = newPlayer.SpawnSpaceship(this);
        playerSpaceship_.lock()->onActorDestoryed_.BindAction(GetWeakRef(), &GameLevelOne::PlayerSpaceshipDestoryed);

        gameplayHUD_ = SpawnHUD<GameplayHUD>();

        gameplayHUD_.lock()->onQuitButtonClicked_.BindAction(GetWeakRef(), &GameLevelOne::QuitGame);
        gameplayHUD_.lock()->onRestartButtonClicked_.BindAction(GetWeakRef(), &GameLevelOne::Restart);
    }

    void GameLevelOne::PlayerSpaceshipDestoryed(Actor *destoryedPlayerSapceship)
    {
        playerSpaceship_ = PlayerManager::Get().GetPlayer()->SpawnSpaceship(this);
        if (!playerSpaceship_.expired())
        {
            playerSpaceship_.lock()->onActorDestoryed_.BindAction(GetWeakRef(), &GameLevelOne::PlayerSpaceshipDestoryed);
        }
        else
        {
            GameOver();
        }
    }

    void GameLevelOne::AllGameStageFinished()
    {
        gameplayHUD_.lock()->GameFinished(true);
    }

    void GameLevelOne::GameOver()
    {
        gameplayHUD_.lock()->GameFinished(false);
        // LOG("Game Over ! ============================================");
    }

    void GameLevelOne::Tick(float DeltaTime)
    {
    }

    void GameLevelOne::InitGameStages()
    {
        AddStage(shared<WaitStage>{new WaitStage{this, 5.f}});
        AddStage(shared<BossStage>{new BossStage{this}});

        // AddStage(shared<WaitStage>{new WaitStage{this, 1.f}});
        // AddStage(shared<VanguardStage>{new VanguardStage{this}});

        // AddStage(shared<WaitStage>{new WaitStage{this, 2.f}});
        // AddStage(shared<TwinBladeStage>{new TwinBladeStage{this}});

        // AddStage(shared<WaitStage>{new WaitStage{this, 2.f}});
        // AddStage(shared<HexagonStage>{new HexagonStage{this}});

        // AddStage(shared<WaitStage>{new WaitStage{this, 4.f}});
        // AddStage(shared<UFOStage>{new UFOStage{this}});

        // AddStage(shared<WaitStage>{new WaitStage{this, 5.f}});
        // AddStage(shared<ChaosStage>{new ChaosStage{this}});

        // AddStage(shared<WaitStage>{new WaitStage{this, 5.f}});
        // AddStage(shared<BossStage>{new BossStage{this}});
    }

    void GameLevelOne::Restart()
    {
        PlayerManager::Get().Reset();
        GetApplication()->LoadWorld<GameLevelOne>();
    }

    void GameLevelOne::QuitGame()
    {
        GetApplication()->QuitApplication();
    }
    void GameLevelOne::SpwanCosmetics()
    {
        auto backdropActor = SpawnActor<BackdropActor>("SpaceShooterRedux/Backgrounds/darkPurple.png");

        weak<BackgroundLayer> planets = SpawnActor<BackgroundLayer>();
        planets.lock()->SetAssets(
            {
                "SpaceShooterRedux/PNG/Planets/Planet1.png",
                "SpaceShooterRedux/PNG/Planets/Planet2.png",
                "SpaceShooterRedux/PNG/Planets/Planet3.png",
                "SpaceShooterRedux/PNG/Planets/Planet4.png",
                "SpaceShooterRedux/PNG/Planets/Planet5.png",
                "SpaceShooterRedux/PNG/Planets/Planet6.png",
                "SpaceShooterRedux/PNG/Planets/Planet7.png",
            });
        planets.lock()->SetSpriteCount(1);
        planets.lock()->SetSizes(1.f, 1.5f);
        planets.lock()->SetVelocities({0, 30.f}, {0, 80.f});

        weak<BackgroundLayer> Meteors = SpawnActor<BackgroundLayer>();
        Meteors.lock()->SetAssets(
            {
                "SpaceShooterRedux/PNG/Meteors/meteorGrey_tiny1.png",
                "SpaceShooterRedux/PNG/Meteors/meteorGrey_tiny2.png",
                "SpaceShooterRedux/PNG/Meteors/meteorGrey_small1.png",
                "SpaceShooterRedux/PNG/Meteors/meteorGrey_small2.png",
                "SpaceShooterRedux/PNG/Meteors/meteorGrey_med1.png",
                "SpaceShooterRedux/PNG/Meteors/meteorGrey_med2.png",
                "SpaceShooterRedux/PNG/Meteors/meteorGrey_big1.png",
                "SpaceShooterRedux/PNG/Meteors/meteorGrey_big2.png",
                "SpaceShooterRedux/PNG/Meteors/meteorGrey_big3.png",
                "SpaceShooterRedux/PNG/Meteors/meteorGrey_big4.png",

                "SpaceShooterRedux/PNG/Meteors/meteorBrown_tiny1.png",
                "SpaceShooterRedux/PNG/Meteors/meteorBrown_tiny2.png",
                "SpaceShooterRedux/PNG/Meteors/meteorBrown_small1.png",
                "SpaceShooterRedux/PNG/Meteors/meteorBrown_small2.png",
                "SpaceShooterRedux/PNG/Meteors/meteorBrown_med1.png",
                "SpaceShooterRedux/PNG/Meteors/meteorBrown_med2.png",
                "SpaceShooterRedux/PNG/Meteors/meteorBrown_big1.png",
                "SpaceShooterRedux/PNG/Meteors/meteorBrown_big2.png",
                "SpaceShooterRedux/PNG/Meteors/meteorBrown_big3.png",
                "SpaceShooterRedux/PNG/Meteors/meteorBrown_big4.png",

            });

        Meteors.lock()->SetSpriteCount(20);
        Meteors.lock()->SetSizes(.2f, .5f);
    }
}

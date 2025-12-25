#include "Level/MainMenuLevel.h"
#include "Level./GameLevelOne.h"
#include "framework/Application.h"
#include "widgets/MainMenuHUD.h"

namespace LightYears
{
    MainMenuLevel::MainMenuLevel(Application *owningApplication)
        : World{owningApplication}
    {
        mainMenuHUD_ = SpawnHUD<MainMenuHUD>();
    }

    void MainMenuLevel::BeginPlay()
    {
        mainMenuHUD_.lock()->onStartButtonClicked_.BindAction(GetWeakRef(), &MainMenuLevel::StartGame);
        mainMenuHUD_.lock()->onQuitButtonClicked_.BindAction(GetWeakRef(), &MainMenuLevel::QuitGame);
    }

    void MainMenuLevel::StartGame()
    {
        GetApplication()->LoadWorld<GameLevelOne>();
    }

    void MainMenuLevel::QuitGame()
    {
        GetApplication()->QuitApplication();
    }
}
#pragma once

#include "framework/World.h"

namespace LightYears
{
    class MainMenuHUD;
    class MainMenuLevel : public World
    {
    public:
        MainMenuLevel(Application *owningApplication);
        virtual void BeginPlay() override;

    private:
        void StartGame();
        void QuitGame();

    private:
        weak<MainMenuHUD> mainMenuHUD_;
    };
}
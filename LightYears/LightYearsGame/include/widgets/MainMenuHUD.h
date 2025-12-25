#pragma once

#include "widgets/HUD.h"
#include "widgets/TextWidget.h"
#include "widgets/Button.h"

namespace LightYears
{
    class MainMenuHUD : public HUD
    {
    public:
        MainMenuHUD();

        virtual void Draw(sf::RenderWindow &windowRef) override;
        virtual bool HandleEvent(const sf::Event &event) override;

    public:
        Delegate<> onStartButtonClicked_;
        Delegate<> onQuitButtonClicked_;

    private:
        virtual void Init(const sf::RenderWindow &windowRef) override;

        void StartButtonClicked();
        void QuitButtonClicked();

    private:
        TextWidget titleText_;
        Button startButton_;
        Button quitButton_;
    };
}
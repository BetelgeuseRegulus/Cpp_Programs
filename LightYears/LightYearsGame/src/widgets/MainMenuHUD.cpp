#include <SFML/Graphics.hpp>
#include "widgets/MainMenuHUD.h"

namespace LightYears
{
    LightYears::MainMenuHUD::MainMenuHUD()
        : titleText_{"Light Years"},
          startButton_{"Start"},
          quitButton_{"Quit"}
    {
        titleText_.SetTextSize(40);
        startButton_.SetTextSize(20);
        quitButton_.SetTextSize(20);
    }

    void MainMenuHUD::Draw(sf::RenderWindow &windowRef)
    {
        titleText_.NativeDraw(windowRef);
        startButton_.NativeDraw(windowRef);
        quitButton_.NativeDraw(windowRef);
    }

    bool MainMenuHUD::HandleEvent(const sf::Event &event)
    {
        return startButton_.HandleEvent(event) ||
               quitButton_.HandleEvent(event) ||
               HUD::HandleEvent(event);
    }

    void MainMenuHUD::Init(const sf::RenderWindow &windowRef)
    {
        sf::Vector2u windowSize = windowRef.getSize();
        titleText_.SetWidgetLocation({windowSize.x / 2.f - titleText_.GetBound().width / 2.f, 100.f});

        startButton_.SetWidgetLocation({windowSize.x / 2.f - startButton_.GetBound().width / 2.f, windowSize.y / 2.f});
        quitButton_.SetWidgetLocation(startButton_.GetWidgetLocation() + sf::Vector2f{0.f, 50.f});

        startButton_.onButtonClicked_.BindAction(GetWeakRef(), &MainMenuHUD::StartButtonClicked);
        quitButton_.onButtonClicked_.BindAction(GetWeakRef(), &MainMenuHUD::QuitButtonClicked);
    }

    void MainMenuHUD::StartButtonClicked()
    {
        onStartButtonClicked_.Broadcast();
    }

    void MainMenuHUD::QuitButtonClicked()
    {
        onQuitButtonClicked_.Broadcast();
    }
}

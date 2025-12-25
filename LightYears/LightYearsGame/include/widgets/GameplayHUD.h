#pragma once

#include "widgets/HUD.h"
#include "widgets/TextWidget.h"
#include "widgets/ValueGuage.h"
#include "widgets/imageWidget.h"
#include "widgets/button.h"

namespace LightYears
{
    class Actor;
    class GameplayHUD : public HUD
    {
    public:
        GameplayHUD();

        virtual void Draw(sf::RenderWindow &windowRef) override;
        virtual void Tick(float deltaTime) override;
        virtual bool HandleEvent(const sf::Event &event) override;

        void GameFinished(bool playerWon);

    public:
        Delegate<> onRestartButtonClicked_;
        Delegate<> onQuitButtonClicked_;

    private:
        virtual void Init(const sf::RenderWindow &windowRef) override;
        void PlayerHealthUpdated(float amt, float currentHealth, float maxHealth);
        void RefreshHealthBar();
        void PlayerSpaceshipDestoryed(Actor *actor);
        void ConnectPlayerPlayerStatus();
        void PlayerLifeCountUpdated(int amt);
        void PlayerScoreUpdated(int newScore);
        void RestartButtonClicked();
        void QuitButtonClicked();

    private:
        TextWidget framerateText_;
        ValueGuage playerHealthBar_;
        ImageWidget playerLifeIcon_;
        TextWidget playerLifeText_;

        ImageWidget playerScoreIcon_;
        TextWidget playerScoreText_;

        // TODO: test and remove then
        // Button testButton_;
        // void TestButtonClick();

        sf::Color healthyHealthBarColor_{};
        sf::Color moderateHealthBarColor_{};
        sf::Color criticalHealthBarColor_{};

        float moderateThreshold_{};
        float criticalThreshold_{};

        float widgetSpacing_{};

        TextWidget winLoseText_;
        TextWidget finalScoreText_;
        Button restartButton_;
        Button quitButton_;

        sf::Vector2u windowSize_{};
    };

}
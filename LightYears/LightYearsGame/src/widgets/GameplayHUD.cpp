#include "widgets/GameplayHUD.h"
#include "framework/Actor.h"
#include "player/PlayerManager.h"
#include "player/PlayerSpaceship.h"
#include "player/Player.h"

namespace LightYears
{
    GameplayHUD::GameplayHUD()
        : framerateText_{"Frame Rate:"},
          playerHealthBar_{},
          playerLifeIcon_{"SpaceShooterRedux/PNG/pickups/playerLife1_blue.png"},
          playerLifeText_{""},
          playerScoreIcon_{"SpaceShooterRedux/PNG/Power-ups/star_gold.png"},
          playerScoreText_{""},
          healthyHealthBarColor_{128, 255, 128, 255},
          moderateHealthBarColor_{255, 128, 0, 255},
          criticalHealthBarColor_{255, 0, 0, 255},
          moderateThreshold_{0.6},
          criticalThreshold_{0.3},
          widgetSpacing_{10.f},
          winLoseText_{""},
          finalScoreText_{""},
          restartButton_{"Restart"},
          quitButton_{"Quit"},
          windowSize_{}
    {
        framerateText_.SetTextSize(30);
        playerLifeText_.SetTextSize(20);
        playerScoreText_.SetTextSize(20);

        winLoseText_.SetVisiblity(false);
        finalScoreText_.SetVisiblity(false);
        restartButton_.SetVisiblity(false);
        quitButton_.SetVisiblity(false);
    }

    void GameplayHUD::Draw(sf::RenderWindow &windowRef)
    {
        windowSize_ = windowRef.getSize();

        framerateText_.NativeDraw(windowRef);
        playerHealthBar_.NativeDraw(windowRef);
        playerLifeIcon_.NativeDraw(windowRef);
        playerLifeText_.NativeDraw(windowRef);

        playerScoreIcon_.NativeDraw(windowRef);
        playerScoreText_.NativeDraw(windowRef);

        winLoseText_.NativeDraw(windowRef);
        finalScoreText_.NativeDraw(windowRef);
        restartButton_.NativeDraw(windowRef);
        quitButton_.NativeDraw(windowRef);
    }

    void GameplayHUD::Tick(float deltaTime)
    {
        int frameRata = static_cast<int>(1 / deltaTime);
        std::string frameRateStr = "Frame Rate: " + std::to_string(frameRata);
        framerateText_.SetString(frameRateStr);
    }

    bool GameplayHUD::HandleEvent(const sf::Event &event)
    {
        if (restartButton_.HandleEvent(event))
            return true;

        if (quitButton_.HandleEvent(event))
            return true;

        return HUD::HandleEvent(event);
    }

    void GameplayHUD::Init(const sf::RenderWindow &windowRef)
    {
        auto windowSize = windowRef.getSize();
        windowSize_ = windowSize;

        playerHealthBar_.SetWidgetLocation(sf::Vector2f{20.f, windowSize.y - 50.f});

        sf::Vector2f nextWidgetPos = playerHealthBar_.GetWidgetLocation();

        nextWidgetPos += sf::Vector2f{playerHealthBar_.GetBound().width + widgetSpacing_, 6.f};
        playerLifeIcon_.SetWidgetLocation(nextWidgetPos);

        nextWidgetPos += sf::Vector2f{playerLifeIcon_.GetBound().width + widgetSpacing_, 0.f};
        playerLifeText_.SetWidgetLocation(nextWidgetPos);

        nextWidgetPos += sf::Vector2f{playerLifeText_.GetBound().width + widgetSpacing_ * 5, -2.f};
        playerScoreIcon_.SetWidgetLocation(nextWidgetPos);

        nextWidgetPos += sf::Vector2f{playerScoreIcon_.GetBound().width + widgetSpacing_, 0.f};
        playerScoreText_.SetWidgetLocation(nextWidgetPos);

        RefreshHealthBar();
        ConnectPlayerPlayerStatus();

        winLoseText_.SetTextSize(40);
        winLoseText_.SetWidgetLocation({windowSize.x / 2.f - winLoseText_.GetBound().width / 2.f, 100.f});

        finalScoreText_.SetTextSize(40);
        finalScoreText_.SetWidgetLocation({windowSize.x / 2.f - finalScoreText_.GetBound().width / 2.f, 200.f});

        restartButton_.SetWidgetLocation({windowSize.x / 2.f - restartButton_.GetBound().width / 2.f, windowSize.y / 2.f});
        quitButton_.SetWidgetLocation(restartButton_.GetWidgetLocation() + sf::Vector2f{0.f, 50.f});

        restartButton_.onButtonClicked_.BindAction(GetWeakRef(), &GameplayHUD::RestartButtonClicked);
        quitButton_.onButtonClicked_.BindAction(GetWeakRef(), &GameplayHUD::QuitButtonClicked);
    }

    void GameplayHUD::PlayerHealthUpdated(float amt, float currentHealth, float maxHealth)
    {
        playerHealthBar_.UpdateValue(currentHealth, maxHealth);

        if (currentHealth / maxHealth <= criticalThreshold_)
        {
            playerHealthBar_.SetForegroundColor(criticalHealthBarColor_);
        }
        else if (currentHealth / maxHealth <= moderateThreshold_)
        {
            playerHealthBar_.SetForegroundColor(moderateHealthBarColor_);
        }
        else
        {
            playerHealthBar_.SetForegroundColor(healthyHealthBarColor_);
        }
    }

    void GameplayHUD::RefreshHealthBar()
    {
        Player *player = PlayerManager::Get().GetPlayer();
        if (player && !player->GetCurrentSpaceship().expired())
        {
            weak<PlayerSpaceship> playerSpaceship = player->GetCurrentSpaceship();
            playerSpaceship.lock()->onActorDestoryed_.BindAction(GetWeakRef(), &GameplayHUD::PlayerSpaceshipDestoryed);
            HealthComponent &healthComp = player->GetCurrentSpaceship().lock()->GetHealthComp();
            healthComp.onHealthChanged_.BindAction(GetWeakRef(), &GameplayHUD::PlayerHealthUpdated);
            PlayerHealthUpdated(0, healthComp.GetHealth(), healthComp.GetMaxHealth());
        }
    }

    void GameplayHUD::PlayerSpaceshipDestoryed(Actor *actor)
    {
        RefreshHealthBar();
    }

    void GameplayHUD::ConnectPlayerPlayerStatus()
    {
        Player *player = PlayerManager::Get().GetPlayer();
        if (player)
        {
            int lifeCount = player->GetLifeCount();
            playerLifeText_.SetString(std::to_string(lifeCount));
            player->onLifeChange_.BindAction(GetWeakRef(), &GameplayHUD::PlayerLifeCountUpdated);

            int playerScore = player->GetScore();
            playerScoreText_.SetString(std::to_string(playerScore));
            player->onScoreChange_.BindAction(GetWeakRef(), &GameplayHUD::PlayerScoreUpdated);
        }
    }

    void GameplayHUD::PlayerLifeCountUpdated(int amt)
    {
        playerLifeText_.SetString(std::to_string(amt));
    }

    void GameplayHUD::PlayerScoreUpdated(int newScore)
    {
        playerScoreText_.SetString(std::to_string(newScore));
    }

    void GameplayHUD::RestartButtonClicked()
    {
        onRestartButtonClicked_.Broadcast();
    }

    void GameplayHUD::QuitButtonClicked()
    {
        onQuitButtonClicked_.Broadcast();
    }

    void GameplayHUD::GameFinished(bool playerWon)
    {
        winLoseText_.SetVisiblity(true);
        finalScoreText_.SetVisiblity(true);
        restartButton_.SetVisiblity(true);
        quitButton_.SetVisiblity(true);

        int score = PlayerManager::Get().GetPlayer()->GetScore();
        finalScoreText_.SetString("Score: " + std::to_string(score));

        if (playerWon)
        {
            winLoseText_.SetString("WIN");
        }
        else
        {
            winLoseText_.SetString("GAME OVER");
        }
        winLoseText_.SetWidgetLocation({windowSize_.x / 2.f - winLoseText_.GetBound().width / 2.f, 100.f});
        finalScoreText_.SetWidgetLocation({windowSize_.x / 2.f - finalScoreText_.GetBound().width / 2.f, 200.f});
    }
}

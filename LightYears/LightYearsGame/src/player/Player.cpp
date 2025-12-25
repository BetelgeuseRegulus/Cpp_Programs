#include "player/Player.h"
#include "framework/World.h"
#include "player/PlayerSpaceship.h"

namespace LightYears
{
    Player::Player()
        : lifeCount_{3},
          score_{0},
          currentPlayerSpaceship_{}
    {
    }

    Player::~Player()
    {
    }

    weak<PlayerSpaceship> Player::SpawnSpaceship(World *world)
    {
        if (lifeCount_ > 0)
        {
            --lifeCount_;

            auto windowSize = world->GetWindowSize();
            currentPlayerSpaceship_ = world->SpawnActor<PlayerSpaceship>();
            currentPlayerSpaceship_.lock()->SetActorLocation(sf::Vector2f(windowSize.x / 2.f, windowSize.y - 100.f));

            onLifeChange_.Broadcast(lifeCount_);

            return currentPlayerSpaceship_;
        }
        else
        {
            currentPlayerSpaceship_ = weak<PlayerSpaceship>{};
            onLifeExhausted_.Broadcast();
        }

        return weak<PlayerSpaceship>{};
    }

    void Player::AddLifeCount(unsigned int count)
    {
        if (count > 0)
        {
            lifeCount_ += count;
            onLifeChange_.Broadcast(lifeCount_);
        }
    }

    void Player::AddScore(unsigned int amt)
    {
        if (amt > 0)
        {
            score_ += amt;
            onScoreChange_.Broadcast(score_);
        }
    }

}

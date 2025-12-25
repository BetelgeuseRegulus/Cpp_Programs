#pragma once
#include "framework/Object.h"
#include "framework/Core.h"

namespace LightYears
{
    class PlayerSpaceship;
    class World;
    class Player : public Object
    {
    public:
        Player();
        ~Player();

        weak<PlayerSpaceship> SpawnSpaceship(World *world);
        const weak<PlayerSpaceship> GetCurrentSpaceship() const { return currentPlayerSpaceship_; }

        void AddLifeCount(unsigned int count);
        int GetLifeCount() const { return lifeCount_; }

        void AddScore(unsigned int amt);
        int GetScore() const { return score_; }

       public:
        Delegate<int> onLifeChange_;
        Delegate<int> onScoreChange_;
        Delegate<> onLifeExhausted_;

    private:
        unsigned int lifeCount_{};
        unsigned int score_{};
        weak<PlayerSpaceship> currentPlayerSpaceship_;
    };
}
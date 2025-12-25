#include "player/PlayerManager.h"

namespace LightYears
{
    unique<PlayerManager> PlayerManager::playerManager_{nullptr};

    PlayerManager::PlayerManager()
    {
    }

    Player &PlayerManager::CreateNewPlayer()
    {
        players_.emplace(players_.begin(), Player());
        return players_.back();
    }

    Player *PlayerManager::GetPlayer(int playerIndex)
    {
        if (playerIndex >= 0 && playerIndex <= players_.size())
        {
            return &(players_[playerIndex]);
        }
        return nullptr;
    }

    const Player *PlayerManager::GetPlayer(int playerIndex) const
    {
        if (playerIndex >= 0 && playerIndex <= players_.size())
        {
            return &(players_[playerIndex]);
        }
        return nullptr;
    }

    PlayerManager &PlayerManager::Get()
    {
        // TODO: insert return statement here
        if (!playerManager_)
        {
            playerManager_ = std::move(unique<PlayerManager>{new PlayerManager{}});
        }

        return *playerManager_;
    }

    void PlayerManager::Reset()
    {
        players_.clear();
    }
}

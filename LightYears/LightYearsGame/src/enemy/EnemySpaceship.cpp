#include "enemy/EnemySpaceship.h"
#include "framework/MathUtility.h"
#include "player/PlayerManager.h"
namespace LightYears
{
    EnemySpaceship::EnemySpaceship(World *owningWorld,
                                   const std::string &texturePath,
                                   float collisionDamage,
                                   float rewardSpawnWeight,
                                   const List<RewardFactoryFunc> rewards)
        : Spaceship{owningWorld, texturePath},
          collisionDamage_{collisionDamage},
          rewardSpawnWeight_{rewardSpawnWeight},
          rewardFactories_{rewards},
          scoreAwardAmt_{10}
    {
        SetTeamID(2);
    }

    void EnemySpaceship::Tick(float deltaTime)
    {
        Spaceship ::Tick(deltaTime);

        if (IsActorOutOfWindowBounds(GetActorGlobalBounds().width * 2.f))
        {
            Destroy();
        }
    }

    void EnemySpaceship::OnActorBeginOverlap(Actor *other)
    {
        Spaceship::OnActorBeginOverlap(other);
        if (IsOtherHostile(other))
        {
            other->ApplyDamage(collisionDamage_);
        }
    }

    void EnemySpaceship::SpawnReward()
    {
        if (rewardFactories_.size() == 0)
            return;

        // 只有 50%的几率,敌方飞船死亡后会生成奖励物品
        if (rewardSpawnWeight_ < RandomRange(0, 1))
        {
            return;
        }

        int pick = static_cast<int>(RandomRange(0, rewardFactories_.size()));
        if (pick >= 0 && pick < rewardFactories_.size())
        {
            // 生成一个随机奖励(医疗包, 三发弹, 肃清者)在敌方飞船爆炸位置
            // using RewardFactoryFunc = std::function<weak<Reward>(World *)>;
            weak<Reward> newReward = rewardFactories_[pick](GetWorld());
            newReward.lock()->SetActorLocation(GetActorLocation());
        }
    }
    void EnemySpaceship::SetScoreAwardAmt(unsigned int amt)
    {
        scoreAwardAmt_ = amt;
    }

    void EnemySpaceship::SetRewardSpawnWeight(float weight)
    {
        if (weight < 0 || weight > 1)
            return;

        rewardSpawnWeight_ = weight;
    }

    void EnemySpaceship::Blew()
    {
        SpawnReward();

        Player *player = PlayerManager::Get().GetPlayer();
        if (player)
        {
            player->AddScore(scoreAwardAmt_);
        }
    }
}
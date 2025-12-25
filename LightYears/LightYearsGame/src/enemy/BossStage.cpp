#include "enemy/BossStage.h"
#include "enemy/Boss.h"
#include "framework/World.h"
#include "framework/Actor.h"

namespace LightYears
{
    LightYears::BossStage::BossStage(World *world)
        : GameStage{world}
    {
    }

    void LightYears::BossStage::StartStage()
    {
        weak<Boss> boss = GetWorld()->SpawnActor<Boss>();
        auto windowSize = GetWorld()->GetWindowSize();
        boss.lock()->SetActorLocation({windowSize.x / 2.f, 200.f});
        boss.lock()->onActorDestoryed_.BindAction(GetWeakRef(), &BossStage::BossDestoryed);
    }

    void LightYears::BossStage::BossDestoryed(Actor *bossActor)
    {
        if (IsPendingDestory())
            return;

        if (GetWorld() && GetWorld()->GetIsBeingDestroyed())
            return;

        FinishStage();
    }

    BossStage::~BossStage()
    {
        if (!boss_.expired())
        {
            boss_.lock()->onActorDestoryed_.Clear();
        }
    }
}

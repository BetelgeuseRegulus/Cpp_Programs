#pragma once
#include "gameplay/GameStage.h"

namespace LightYears
{
    class Boss;
    class Actor;
    class BossStage : public GameStage
    {
    public:
        BossStage(World *world);
        virtual ~BossStage();
        virtual void StartStage() override;

    private:
        void BossDestoryed(Actor *bossActor);

    private:
        weak<Boss> boss_;
    };
}
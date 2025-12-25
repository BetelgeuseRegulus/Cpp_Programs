#include "gameplay/WaitStage.h"
#include "framework/TimerManager.h"

namespace LightYears
{
    WaitStage::WaitStage(World *world, float waitDuration)
        : GameStage{world},
          waitDuration_{waitDuration}
    {
    }

    void WaitStage::StartStage()
    {
        TimerManager::Get().SetTimer(GetWeakRef(), &WaitStage::FinishStage, waitDuration_);
    }
}
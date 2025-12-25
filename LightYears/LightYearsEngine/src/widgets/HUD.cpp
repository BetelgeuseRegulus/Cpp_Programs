#include "widgets/HUD.h"

namespace LightYears
{
    void HUD::NativeInit(const sf::RenderWindow &windowRef)
    {
        if (!alreadyInit_)
        {
            alreadyInit_ = true;
            Init(windowRef);
        }
    }

    bool HUD::HandleEvent(const sf::Event &event)
    {
        return false;
    }

    void HUD::Tick(float deltaTime)
    {
    }

    LightYears::HUD::HUD()
        : alreadyInit_{false}
    {
    }

    void HUD::Init(const sf::RenderWindow &windowRef)
    {
    }
}

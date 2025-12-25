#pragma once
#include <SFML/Graphics.hpp>
#include "framework/Object.h"

namespace LightYears
{
    class HUD : public Object
    {
    public:
        virtual void Draw(sf::RenderWindow &windowRef) = 0;
        void NativeInit(const sf::RenderWindow &windowRef);
        bool HasInit() { return alreadyInit_; }

        virtual bool HandleEvent(const sf::Event &event);
        virtual void Tick(float deltaTime);

    protected:
        HUD();

    private:
        virtual void Init(const sf::RenderWindow &windowRef);

    private:
        bool alreadyInit_;
    };
}
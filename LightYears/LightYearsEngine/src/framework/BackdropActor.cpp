#include "framework/BackdropActor.h"
#include "framework/World.h"

namespace LightYears
{
    BackdropActor::BackdropActor(World *owningWorld,
                                 const std::string &texturePath,
                                 const sf::Vector2f velocity)
        : Actor{owningWorld, texturePath},
          movingVelocity_{velocity},
          leftShift_{0},
          topShift_{0}
    {
        auto windowSize = owningWorld->GetWindowSize();
        GetSprite().setOrigin(0.f, 0.f);
        GetSprite().setTextureRect(sf::IntRect{sf::Vector2i{0, 0},
                                               sf::Vector2i{static_cast<int>(windowSize.x),
                                                            static_cast<int>(windowSize.y)}});

        SetTextureRepeated(true);
    }

    void BackdropActor::Tick(float deltaTime)
    {
        Actor::Tick(deltaTime);

        leftShift_ += deltaTime * movingVelocity_.x;
        topShift_ += deltaTime * movingVelocity_.y;

        sf::IntRect currentRect = GetSprite().getTextureRect();
        currentRect.left = leftShift_;
        currentRect.top = topShift_;

        GetSprite().setTextureRect(currentRect);
    }
}

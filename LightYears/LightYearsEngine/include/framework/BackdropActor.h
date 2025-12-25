#pragma once

#include "framework/Actor.h"
namespace LightYears
{
    class BackdropActor : public Actor
    {
    public:
        BackdropActor(World *owningWorld,
                      const std::string &texturePath,
                      const sf::Vector2f velocity = sf::Vector2f{0.f, -50.f});
        virtual void Tick(float deltaTime) override;

    private:
        sf::Vector2f movingVelocity_;

        float leftShift_{};
        float topShift_{};
    };

} // namespace LightYears

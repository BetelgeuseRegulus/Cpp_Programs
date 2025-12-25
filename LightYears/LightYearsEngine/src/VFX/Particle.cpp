#include "VFX/Particle.h"
#include "framework/MathUtility.h"

namespace LightYears
{
    Particle::Particle(World *owningWorld, const std::string &texturePath)
        : Actor{owningWorld, texturePath},
          velocity_{},
          lifeTime_{1.f},
          timer_{}
    {
    }

    void Particle::Tick(float deltaTime)
    {
        Actor::Tick(deltaTime);

        Move(deltaTime);
        Fade(deltaTime);

        if (timer_.getElapsedTime().asSeconds() >= lifeTime_)
        {
            Destroy();
        }
    }

    void Particle::RandomVelocity(float minSpeed, float maxSpeed)
    {
        velocity_ = RandomUnitVector() * RandomRange(minSpeed, maxSpeed);
    }

    void Particle::RandomSize(float min, float max)
    {
        float randScale = RandomRange(min, max);
        GetSprite().setScale(randScale, randScale);
    }

    void Particle::RandomLifeTime(float min, float max)
    {
        lifeTime_ = RandomRange(min, max);
    }

    void Particle::Move(float deltaTime)
    {
        AddActorLocationOffset(velocity_ * deltaTime);
    }

    void Particle::Fade(float deltaTime)
    {
        float elapsedTime = timer_.getElapsedTime().asSeconds();
        GetSprite().setColor(LerpColor(GetSprite().getColor(), sf::Color(255, 255, 255, 0), elapsedTime / lifeTime_));
        GetSprite().setScale(LerpVector(GetSprite().getScale(), sf::Vector2f{0, 0}, elapsedTime / lifeTime_));
    }
}
#include "VFX/Explosion.h"
#include "VFX/Particle.h"
#include "framework/MathUtility.h"
#include "framework/World.h"

namespace LightYears
{
    Explosion::Explosion(int particleAmt,
                         float lifeTimeMin, float lifeTimeMax,
                         float sizeMin, float sizeMax,
                         float speedMin, float speedMax,
                         const sf::Color &particleColor,
                         const List<std ::string> &particleImagePaths)
        : particleAmt_{particleAmt},
          lifeTimeMin_{lifeTimeMin},
          lifeTimeMax_{lifeTimeMax},
          sizeMin_{sizeMin},
          sizeMax_{sizeMax},
          speedMin_{speedMin},
          speedMax_{speedMax},
          particleColor_{particleColor},
          particleImagePaths_{particleImagePaths}
    {
    }

    /**
     * @brief 生成一个爆炸图像, 由多个爆炸粒子(图像)组成
     *
     * @param world
     * @param location
     */
    void Explosion::SpawnExplosion(World *world, const sf::Vector2f &location)
    {
        if (!world)
        {
            return;
        }

        for (int i = 0; i < particleAmt_; ++i)
        {
            std::string particleImagePath = particleImagePaths_[static_cast<int>(RandomRange(0, particleImagePaths_.size() - 0.001f))];
            weak<Particle> newParticle = world->SpawnActor<Particle>(particleImagePath);

            newParticle.lock()->RandomLifeTime(lifeTimeMin_, lifeTimeMax_);
            newParticle.lock()->SetActorLocation(location);
            newParticle.lock()->RandomSize(sizeMin_, sizeMax_);
            newParticle.lock()->RandomVelocity(speedMin_, speedMax_);
            newParticle.lock()->GetSprite().setColor(particleColor_);
        }
    }
} // namespace LightYears

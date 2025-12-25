#pragma once
#include <string>

#include "framework/Core.h"
#include <SFML/Graphics.hpp>

// Amt = amount 数量
namespace LightYears
{
    class World;
    class Explosion
    {
    public:
        Explosion(int particleAmt = 20,
                  float lifeTimeMin = 0.5f, float lifeTimeMax = 1.5f,
                  float sizeMin = 1, float sizeMax = 3,
                  float speedMin = 200, float speedMax = 400,
                  const sf::Color &particleColor = sf::Color{255, 128, 0, 255},
                  /*
                   这里 没有const 不通过编译的原因
                   sf::Color{255, 128, 0, 255}, 这里创建一个临时对象也就是右值(RValue),
                   非常量引用不能绑定到 临时对象(右值),因为临时对象可能在表达式结束后立即销毁
                   常量引用可以绑定到临时对象, 因为const承诺不会修改对象, 编译器会延长临时对象的生命周期到引用的作用域结束
                  */
                  const List<std ::string> &particleImagePaths =
                      {
                          "SpaceShooterRedux/PNG/Effects/star1.png",
                          "SpaceShooterRedux/PNG/Effects/star2.png",
                          "SpaceShooterRedux/PNG/Effects/star3.png",
                      });

        void SpawnExplosion(World *world, const sf::Vector2f &location);

    private:
        int particleAmt_{};

        float lifeTimeMin_{};
        float lifeTimeMax_{};
        float sizeMin_{};
        float sizeMax_{};
        float speedMin_{};
        float speedMax_{};
        sf::Color particleColor_{};
        List<std::string> particleImagePaths_{};
    };
}
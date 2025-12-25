#include <cmath>
#include <random>
#include <chrono>

#include "framework/MathUtility.h"
namespace LightYears
{
    const float PI = 3.1415926535; // Π弧度 = 180° ==> 1° = Π弧度/180, 1弧度 = 180°/Π

    sf::Vector2f RotationToVector(float rotation)
    {
        float radians = DegreesToRadians(rotation - 90.f);

        return sf::Vector2f(std::cos(radians), std::sin(radians));
    }

    float VectorToRotation(const sf::Vector2f &vector)
    {
        // 计算向量的角度
        // atan2 返回的是弧度，范围是 [-π, π]
        float radians = std::atan2(vector.y, vector.x);
        float degrees = RadiansToDegrees(radians);

        // 加90度是因为 SFML 的 0° 指向右边，我们希望 0° 指向上边
        return degrees + 90.f;
    }

    float DegreesToRadians(float degrees)
    {
        return degrees * (PI / 180.f);
    }

    float RadiansToDegrees(float radians)
    {
        return radians * (180.f / PI);
    }

    /**
     * @brief 在 min 和 max 之间生成一个随机浮点数
     *
     * @param min
     * @param max
     * @return float
     */
    float RandomRange(float min, float max)
    {
        // std::random_device rd;
        // std::mt19937 gen(rd());

        // 使用高精度时钟作为种子
        auto seed = std::chrono::high_resolution_clock::now().time_since_epoch().count();
        std::mt19937 gen(seed);

        std::uniform_real_distribution<float> distribution{min, max};

        return distribution(gen);
    }
    /**
     * @brief 生成一个随机方向的单位向量
     *
     * @return sf::Vector2f
     */
    sf::Vector2f RandomUnitVector()
    {
        float randomX = RandomRange(-1, 1);
        float randomY = RandomRange(-1, 1);
        sf::Vector2f randVec{randomX, randomY};
        Normalize(randVec);

        return randVec;
    }

    float LerpFloat(float a, float b, float alpha)
    {
        if (alpha > 1)
            alpha = 1;
        if (alpha < 0)
            alpha = 0;

        return a + (b - a) * alpha;
    }

    sf::Color LerpColor(const sf::Color &a, const sf::Color &b, float alpha)
    {
        int lerpR = LerpFloat(a.r, b.r, alpha);
        int lerpG = LerpFloat(a.g, b.g, alpha);
        int lerpB = LerpFloat(a.b, b.b, alpha);
        int lerpA = LerpFloat(a.a, b.a, alpha);

        return sf::Color(lerpR, lerpG, lerpB, lerpA);
    }

    sf::Vector2f LerpVector(const sf::Vector2f &a, const sf::Vector2f &b, float alpha)
    {
        float lerpX = LerpFloat(a.x, b.x, alpha);
        float lerpY = LerpFloat(a.y, b.y, alpha);

        return sf::Vector2f(lerpX, lerpY);
    }
} // namespace LightYears

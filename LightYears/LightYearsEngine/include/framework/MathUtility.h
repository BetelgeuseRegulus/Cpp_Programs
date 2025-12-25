#pragma once
#include <SFML/Graphics.hpp>
#include <cmath>

namespace LightYears
{
    /**
     * @brief 把旋转角度转换为方向向量
     * @note  此函数使用的美术资源默认朝向为"向上", 因此 0° 对应向上方向 (0, -1)，而非 SFML 默认的向右 (1, 0)
     * @param rotation 旋转角度(单位度)
     * @return sf::Vector2f 单位向量,表示该角度指向的方向.
     */
    sf::Vector2f RotationToVector(float rotation);
    /**
     * @brief 度数转弧度
     *
     * @param degress 度数
     * @return float 转换后弧度
     */
    float DegreesToRadians(float degress);
    /**
     * @brief 弧度转度数
     *
     * @param radians 弧度
     * @return float 转换后度数
     */
    float RadiansToDegrees(float radians);

    float VectorToRotation(const sf::Vector2f &vertor);

    template <typename T>
    float GetVectorLength(sf::Vector2<T> &vector)
    {
        return std::sqrt(vector.x * vector.x + vector.y * vector.y);
    }

    template <typename T>
    sf::Vector2<T> &ScaleVector(sf::Vector2<T> &vectorToScale, float amt)
    {
        vectorToScale.x *= amt;
        vectorToScale.y *= amt;
        return vectorToScale;
    }

    template <typename T>
    sf::Vector2<T> &Normalize(sf::Vector2<T> &vector)
    {
        float vectorLength = GetVectorLength<T>(vector);

        if (vectorLength == 0.f)
            return vector;

        ScaleVector(vector, 1.0 / vectorLength);

        return vector;
    }

    /**
     * @brief 颜色线性插值: 让颜色a平滑过渡到颜色b
     *
     * @param a
     * @param b
     * @param alpha
     * @return sf::Vector2f
     */
    sf::Color LerpColor(const sf::Color &a, const sf::Color &b, float alpha);

    /**
     * @brief 2维坐标线性差值: 让一个2d坐标从a平滑移动到b
     *
     * @param a
     * @param b
     * @param alpha
     * @return sf::Vector2f
     */
    sf::Vector2f LerpVector(const sf::Vector2f &a, const sf::Vector2f &b, float alpha);

    /**
     * @brief 线性插值, 在 a 和 b 之间按照比例 alpha 取一个中间值
     *
     * @param a
     * @param b
     * @param alpha
     * @return sf::Color
     */
    float LerpFloat(float a, float b, float alpha);

    float RandomRange(float min, float max);

    sf::Vector2f RandomUnitVector();
}
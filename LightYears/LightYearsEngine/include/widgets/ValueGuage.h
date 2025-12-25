#pragma once
#include "widgets/Widget.h"

namespace LightYears
{
    /**
     * @brief ValueGuage: 数值计量表
     *
     */
    class ValueGuage : public Widget
    {
    public:
        ValueGuage(const sf::Vector2f &size = sf::Vector2f{300.f, 40.f},
                   float initialPercent = 0.75f,
                   const sf::Color &foregroundColor = sf::Color{128, 255, 128, 255},
                   const sf::Color &backgroundColor = sf::Color{128, 128, 128, 255});

        void UpdateValue(float value, float maxValue);

        virtual sf::FloatRect GetBound() const override;

        void SetTextSize(unsigned int characterSize);

        void SetForegroundColor(const sf::Color &color);
        void SetBackgroundColor(const sf::Color &color);

    private:
        virtual void Draw(sf::RenderWindow &windowRef) override;
        virtual void LocationUpdated(const sf::Vector2f &newLoaction) override;
        virtual void RotationUpdated(float newRotation) override;

        // void UpdateBarColor(float percent);
        void CenterText();

    private:
        shared<sf::Font> textFont_{};
        sf::Text text_{};

        sf::RectangleShape barFront_{};
        sf::RectangleShape barBack_{};

        float percent_{};

        sf::Color foregroundColor_{};
        sf::Color backgroundColor_{};
    };
}
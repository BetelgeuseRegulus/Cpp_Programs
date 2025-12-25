#include "widgets/ValueGuage.h"
#include "framework/AssetManager.h"

namespace LightYears
{
    LightYears::ValueGuage::ValueGuage(const sf::Vector2f &size,
                                       float initialPercent,
                                       const sf::Color &foregroundColor,
                                       const sf::Color &backgroundColor)
        : textFont_{AssetManager::Get().LoadFont("SpaceShooterRedux/Bonus/kenvector_future.ttf")},
          text_{"", *(textFont_.get())},
          barFront_{size},
          barBack_{size},
          percent_{initialPercent},
          foregroundColor_{foregroundColor},
          backgroundColor_{backgroundColor}
    {
        barFront_.setFillColor(foregroundColor);
        barBack_.setFillColor(backgroundColor);
        SetTextSize(25);
    }

    void ValueGuage::UpdateValue(float value, float maxValue)
    {
        if (maxValue == 0)
            return;

        percent_ = value / maxValue;
        //  UpdateBarColor(percent_);

        std::string displayStr = std::to_string(static_cast<int>(value)) + "/" + std::to_string(static_cast<int>(maxValue));
        text_.setString(displayStr);
        //  text_.setPosition((barBack_.getGlobalBounds().getSize().x / 2 - text_.getGlobalBounds().getSize().x / 2) + 20, 930);

        sf::Vector2f barSize = barBack_.getSize();
        barFront_.setSize({barSize.x * percent_, barSize.y});

        CenterText();
    }

    void ValueGuage::LocationUpdated(const sf::Vector2f &newLoaction)
    {
        text_.setPosition(newLoaction);
        barFront_.setPosition(newLoaction);
        barBack_.setPosition(newLoaction);
    }
    void ValueGuage::RotationUpdated(float newRotation)
    {
        text_.setRotation(newRotation);
        barFront_.setRotation(newRotation);
        barBack_.setRotation(newRotation);
    }

    void ValueGuage::Draw(sf::RenderWindow &windowRef)
    {
        windowRef.draw(barBack_);
        windowRef.draw(barFront_);
        windowRef.draw(text_);
    }

    // void ValueGuage::UpdateBarColor(float percent)
    // {
    //     if (percent <= 0.3f)
    //     {
    //         foregroundColor_ = sf::Color{255, 0, 0, 255};
    //     }
    //     else if (percent <= 0.6f)
    //     {
    //         foregroundColor_ = sf::Color{255, 128, 0, 255};
    //     }
    //     else
    //     {
    //         foregroundColor_ = sf::Color{128, 255, 128, 255};
    //     }
    //
    //     barFront_.setFillColor(foregroundColor_);
    // }

    sf::FloatRect ValueGuage::GetBound() const
    {
        return barBack_.getGlobalBounds();
    }

    void ValueGuage::CenterText()
    {
        sf::Vector2f widgetCenter = GetCenterPosition();
        sf::FloatRect textBound = text_.getGlobalBounds();

        text_.setPosition(widgetCenter - sf::Vector2f{textBound.width / 2.f, textBound.height});
    }

    void ValueGuage::SetTextSize(unsigned int characterSize)
    {
        text_.setCharacterSize(characterSize);
    }

    void ValueGuage::SetForegroundColor(const sf::Color &color)
    {
        barFront_.setFillColor(color);
    }
    void ValueGuage::SetBackgroundColor(const sf::Color &color)
    {
        barBack_.setFillColor(color);
    }
}

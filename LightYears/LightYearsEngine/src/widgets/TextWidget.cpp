#include "widgets/TextWidget.h"
#include "framework/AssetManager.h"

namespace LightYears
{
    LightYears::TextWidget::TextWidget(const std::string &textStr,
                                       const std::string &fontPath,
                                       unsigned int characterSize)
        : font_{AssetManager::Get().LoadFont(fontPath)},
          text_{textStr, *(font_.get()), characterSize}
    {
    }

    void LightYears::TextWidget::SetString(const std::string &newStr)
    {
        text_.setString(newStr);
    }

    void LightYears::TextWidget::SetTextSize(unsigned int newSize)
    {
        text_.setCharacterSize(newSize);
    }

    void TextWidget::LocationUpdated(const sf::Vector2f &newLocation)
    {
        text_.setPosition(newLocation);
    }

    void TextWidget::RotationUpdated(float newRotation)
    {
        text_.setRotation(newRotation);
    }

    void TextWidget::Draw(sf::RenderWindow &windowRef)
    {
        windowRef.draw(text_);
    }

    sf::FloatRect TextWidget::GetBound() const
    {
        return text_.getGlobalBounds();
    }
}

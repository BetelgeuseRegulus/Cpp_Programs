#include "Widgets/ImageWidget.h"
#include "framework/AssetManager.h"

namespace LightYears
{
    LightYears::ImageWidget::ImageWidget(const std::string &imagePath)
        : texture_{AssetManager::Get().LoadTexture(imagePath)},
          sprite_{*(texture_.get())}
    {
    }

    void LightYears::ImageWidget::SetImage(const shared<sf::Texture> &newTexture)
    {
        if (newTexture)
        {
            texture_ = newTexture;
            sprite_.setTexture(*(texture_.get()));
        }
    }

    sf::FloatRect ImageWidget::GetBound() const
    {
        return sprite_.getGlobalBounds();
    }

    void LightYears::ImageWidget::LocationUpdated(const sf::Vector2f &newLocation)
    {
        sprite_.setPosition(newLocation);
    }

    void LightYears::ImageWidget::RotationUpdated(float newRotation)
    {
        sprite_.setRotation(newRotation);
    }

    void LightYears::ImageWidget::Draw(sf::RenderWindow &windowRef)
    {
        windowRef.draw(sprite_);
    }
}
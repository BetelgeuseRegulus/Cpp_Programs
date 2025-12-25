#pragma once

#include "widgets/Widget.h"
#include "framework/Delegate.h"

namespace LightYears
{
    class Button : public Widget
    {
    public:
        Button(const std::string &textString = "Button",
               const std::string &buttonTexturePath = "SpaceShooterRedux/PNG/UI/buttonBlue.png");

        virtual sf::FloatRect GetBound() const;
        void SetTextString(const std::string &newStr);
        void SetTextSize(unsigned int characterSize);

        virtual bool HandleEvent(const sf::Event &windowEvent) override;

    public:
        Delegate<> onButtonClicked_;

    private:
        virtual void Draw(sf::RenderWindow &windowRef) override;
        virtual void LocationUpdated(const sf::Vector2f &newLocation) override;
        virtual void RotationUpdated(float newRotation) override;
        void CenterText();

        void ButtonUp();
        void ButtonDown();
        void MouseHovered();

    private:
        shared<sf::Texture> buttonTexture_;
        sf::Sprite buttonSprite_;

        shared<sf::Font> buttonFont_;
        sf::Text buttonText_;

        sf::Color buttonDefaultColor_;
        sf::Color buttonDownColor_;
        sf::Color buttonHoverColor_;

        bool isButtonDown_;
    };
}
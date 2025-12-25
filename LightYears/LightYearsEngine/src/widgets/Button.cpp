#include "widgets/Button.h"
#include "framework/AssetManager.h"

namespace LightYears
{
    Button::Button(const std::string &textString, const std::string &buttonTexturePath)
        : buttonTexture_{AssetManager::Get().LoadTexture(buttonTexturePath)},
          buttonSprite_{*(buttonTexture_.get())},
          buttonFont_{AssetManager::Get().LoadFont("SpaceShooterRedux/Bonus/kenvector_future.ttf")},
          buttonText_{textString, *(buttonFont_.get())},
          buttonDefaultColor_{128, 128, 128, 255},
          buttonDownColor_{64, 64, 64, 255},
          buttonHoverColor_{190, 190, 190, 255},
          isButtonDown_{false}
    {
        buttonSprite_.setColor(buttonDefaultColor_);
    }

    sf::FloatRect Button::GetBound() const
    {
        return buttonSprite_.getGlobalBounds();
    }

    void Button::SetTextString(const std::string &newStr)
    {
        buttonText_.setString(newStr);
        CenterText();
    }

    void Button::SetTextSize(unsigned int characterSize)
    {
        buttonText_.setCharacterSize(characterSize);
        CenterText();
    }

    bool Button::HandleEvent(const sf::Event &windowEvent)
    {
        if (!GetVisiblity())
            return false;

        bool handle = false;

        if (windowEvent.type == sf::Event::MouseButtonReleased)
        {
            if (windowEvent.mouseButton.button == sf::Mouse::Left)
            {
                if (buttonSprite_.getGlobalBounds().contains(windowEvent.mouseButton.x, windowEvent.mouseButton.y) && isButtonDown_)
                {
                    onButtonClicked_.Broadcast();
                    handle = true;
                }
            }
            ButtonUp();
        }
        else if (windowEvent.type == sf::Event::MouseButtonPressed)
        {
            if (buttonSprite_.getGlobalBounds().contains(windowEvent.mouseButton.x, windowEvent.mouseButton.y))
            {
                ButtonDown();
                handle = true;
            }
        }
        else if (windowEvent.type == sf::Event::MouseMoved)
        {
            // 当鼠标在按钮区域移动且没有在按钮区域按下左键时, 设置为鼠标悬挂状态
            if (!sf::Mouse::isButtonPressed(sf::Mouse::Left))
            {
                if (buttonSprite_.getGlobalBounds().contains(windowEvent.mouseMove.x, windowEvent.mouseMove.y))
                {
                    MouseHovered();
                }
                else
                {
                    ButtonUp();
                }
            }
        }

        return handle || Widget::HandleEvent(windowEvent);
    }

    void Button::Draw(sf::RenderWindow &windowRef)
    {
        windowRef.draw(buttonSprite_);
        windowRef.draw(buttonText_);
    }

    void Button::LocationUpdated(const sf::Vector2f &newLocation)
    {
        buttonSprite_.setPosition(newLocation);
        CenterText();
    }

    void Button::RotationUpdated(float newRotation)
    {
        buttonSprite_.setRotation(newRotation);
        buttonText_.setRotation(newRotation);
    }

    void Button::CenterText()
    {
        sf::Vector2f widgetCenter = GetCenterPosition();
        sf::FloatRect textBound = buttonText_.getGlobalBounds();
        buttonText_.setPosition(widgetCenter - sf::Vector2f{textBound.width / 2.f, textBound.height});
    }

    void Button::ButtonUp()
    {
        isButtonDown_ = false;
        buttonSprite_.setColor(buttonDefaultColor_);
    }

    void Button::ButtonDown()
    {
        isButtonDown_ = true;
        buttonSprite_.setColor(buttonDownColor_);
    }

    void Button::MouseHovered()
    {
        buttonSprite_.setColor(buttonHoverColor_);
    }
}
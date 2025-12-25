#include "Widgets/Widget.h"

namespace LightYears
{
    void Widget::NativeDraw(sf::RenderWindow &windowRef)
    {
        if (isVisible_)
        {
            Draw(windowRef);
        }
    }

    bool Widget::HandleEvent(const sf::Event &event)
    {
        return false;
    }

    void Widget::SetWidgetLocation(const sf::Vector2f &newLocation)
    {
        widgetTransform_.setPosition(newLocation);
        LocationUpdated(newLocation);
    }

    void Widget::SetWidgetRotation(float newRolation)
    {
        widgetTransform_.setRotation(newRolation);
        RotationUpdated(newRolation);
    }

    void Widget::SetVisiblity(bool newVisiility)
    {
        isVisible_ = newVisiility;
    }

    Widget::Widget()
        : isVisible_{true},
          widgetTransform_{}
    {
    }

    sf::Vector2f Widget::GetCenterPosition() const
    {
        sf::FloatRect bound = GetBound();
        return sf::Vector2f(bound.left + bound.width / 2.f, bound.top + bound.height / 2.f);
    }

    void Widget::Draw(sf::RenderWindow &windowRef)
    {
    }

    void Widget::LocationUpdated(const sf::Vector2f &newLocation)
    {
    }

    void Widget::RotationUpdated(float)
    {
    }
}

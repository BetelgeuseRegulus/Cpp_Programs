#pragma once

#include <SFML/graphics.hpp>
#include "framework/Object.h"

namespace LightYears
{
    class Widget : public Object
    {
    public:
        void NativeDraw(sf::RenderWindow &windowRef);
        virtual bool HandleEvent(const sf::Event &event);

        void SetWidgetLocation(const sf::Vector2f &newLocation);
        sf::Vector2f GetWidgetLocation() const { return widgetTransform_.getPosition(); }

        void SetWidgetRotation(float newRolation);
        float GetWidgetRotation() const { return widgetTransform_.getRotation(); }

        void SetVisiblity(bool newVisiility);
        bool GetVisiblity() const { return isVisible_; }

        virtual sf::FloatRect GetBound() const = 0;
        sf::Vector2f GetCenterPosition() const;

    protected:
        Widget();

    private:
        virtual void Draw(sf::RenderWindow &windowRef);
        virtual void LocationUpdated(const sf::Vector2f &newLocation);
        virtual void RotationUpdated(float newRotation);

    private:
        sf::Transformable widgetTransform_{};
        bool isVisible_{};
    };
}
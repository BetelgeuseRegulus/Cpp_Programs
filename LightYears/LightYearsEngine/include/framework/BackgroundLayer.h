#pragma once

#include "framework/Actor.h"

namespace LightYears
{
    class BackgroundLayer : public Actor
    {
    public:
        BackgroundLayer(World *owningWorld,
                        const List<std::string> &assetpaths = {},
                        const sf::Vector2f &minVelocity = sf::Vector2f{0.f, 50.f},
                        const sf::Vector2f &maxVelocity = sf::Vector2f{0.f, 200.f},
                        float sizeMin = 1.f,
                        float sizeMax = 2.f,
                        int spriteCount = 20,
                        const sf::Color &colorTint = sf::Color{180, 180, 200, 225});

        void SetAssets(const List<std::string> &assetPaths);
        void SetColorTint(const sf::Color &color);
        void SetSpriteCount(int newCount);
        void SetVelocities(const sf::Vector2f &min, const sf::Vector2f &max);
        void SetSizes(float min, float max);

        virtual void Render(sf::RenderWindow &windowRef) override;
        virtual void Tick(float deltaTime) override;

    private:
        void RefreshSprites();
        void RandomSpriteTexture(sf::Sprite &sprite);
        void RandomSpriteTransform(sf::Sprite &sprite, bool randomY = false);
        void RandomSpritePosition(sf::Sprite &sprite, bool randomY);
        void RandomSpriteRotation(sf::Sprite &sprite);
        void RandomSpriteSize(sf::Sprite &sprite);

        bool IsSpriteOffScreen(sf::Sprite &sprite) const;

        shared<sf::Texture> GetRandomTexture() const;

    private:
        sf::Vector2f minVelocity_{};
        sf::Vector2f maxVelocity_{};

        float sizeMin_{};
        float sizeMax_{};

        int spriteCount_{};
        sf::Color tintColor_{};

        List<sf::Sprite> sprites_;
        List<shared<sf::Texture>> textures_;
        List<sf::Vector2f> velocities_;
    };
}
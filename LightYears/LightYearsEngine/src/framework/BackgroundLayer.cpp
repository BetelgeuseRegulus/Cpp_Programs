#include "framework/BackgroundLayer.h"
#include "framework/World.h"
#include "framework/MathUtility.h"
#include "framework/AssetManager.h"

namespace LightYears
{
    BackgroundLayer::BackgroundLayer(World *owningWorld,
                                     const List<std::string> &assetpaths,
                                     const sf::Vector2f &minVelocity,
                                     const sf::Vector2f &maxVelocity,
                                     float sizeMin, float sizeMax,
                                     int spriteCount,
                                     const sf::Color &colorTint)
        : Actor{owningWorld},
          minVelocity_{minVelocity},
          maxVelocity_{maxVelocity},
          sizeMin_{sizeMin},
          sizeMax_{sizeMax_},
          spriteCount_{spriteCount},
          tintColor_{colorTint}
    {
        SetAssets(assetpaths);
        SetEnablePhysics(false);
    }

    void BackgroundLayer::SetAssets(const List<std::string> &assetPaths)
    {
        for (const std::string &texturesPath : assetPaths)
        {
            shared<sf::Texture> newTexture = AssetManager::Get().LoadTexture(texturesPath);
            textures_.push_back(newTexture);
        }

        RefreshSprites();
    }

    void BackgroundLayer::RefreshSprites()
    {
        sprites_.clear();
        velocities_.clear();

        for (int i = 0; i < spriteCount_; ++i)
        {
            sf::Sprite newSprite{};
            RandomSpriteTexture(newSprite);
            RandomSpriteTransform(newSprite, true);
            sprites_.push_back(newSprite);

            float velX = RandomRange(minVelocity_.x, maxVelocity_.x);
            float velY = RandomRange(minVelocity_.y, maxVelocity_.y);

            velocities_.push_back(sf::Vector2f{velX, velY});
        }

        SetColorTint(tintColor_);
    }

    void BackgroundLayer::RandomSpriteTexture(sf::Sprite &sprite)
    {
        if (textures_.size() > 0)
        {
            shared<sf::Texture> pickedTexture = GetRandomTexture();
            sprite.setTexture(*(pickedTexture.get()));
            sprite.setTextureRect(sf::IntRect(0,
                                              0,
                                              static_cast<int>(pickedTexture->getSize().x),
                                              static_cast<int>(pickedTexture->getSize().y)));
            sf::FloatRect bound = sprite.getGlobalBounds();
            sprite.setOrigin(bound.width / 2.f, bound.height / 2.f);
        }
    }

    void BackgroundLayer::RandomSpriteTransform(sf::Sprite &sprite, bool randomY)
    {
        RandomSpritePosition(sprite, randomY);
        RandomSpriteRotation(sprite);
        RandomSpriteSize(sprite);
    }

    void BackgroundLayer::RandomSpritePosition(sf::Sprite &sprite, bool randomY)
    {
        auto windowSize = GetWorld()->GetWindowSize();
        auto bound = sprite.getGlobalBounds();

        float posX = RandomRange(0, windowSize.x);
        float posY = randomY ? RandomRange(0, windowSize.y) : -bound.height;

        sprite.setPosition(sf::Vector2f{posX, posY});
    }

    void BackgroundLayer::RandomSpriteRotation(sf::Sprite &sprite)
    {
        sprite.setRotation(RandomRange(0, 360.f));
    }

    void BackgroundLayer::RandomSpriteSize(sf::Sprite &sprite)
    {
        float size = RandomRange(sizeMin_, sizeMax_);

        sprite.setScale(size, size);
    }

    void BackgroundLayer::SetColorTint(const sf::Color &color)
    {
        tintColor_ = color;
        for (sf::Sprite &sprite : sprites_)
        {
            sprite.setColor(color);
        }
    }

    void BackgroundLayer::SetSpriteCount(int newCount)
    {
        spriteCount_ = newCount;
        RefreshSprites();
    }

    void BackgroundLayer::SetVelocities(const sf::Vector2f &min, const sf::Vector2f &max)
    {
        minVelocity_ = min;
        maxVelocity_ = max;

        for (int i = 0; i < velocities_.size(); ++i)
        {
            float velX = RandomRange(minVelocity_.x, maxVelocity_.x);
            float velY = RandomRange(minVelocity_.y, maxVelocity_.y);

            velocities_[i] = sf::Vector2f{velX, velY};
        }
    }

    void BackgroundLayer::SetSizes(float min, float max)
    {
        sizeMin_ = min;
        sizeMax_ = max;

        for (int i = 0; i < sprites_.size(); ++i)
        {
            RandomSpriteSize(sprites_[i]);
        }
    }

    void BackgroundLayer::Render(sf::RenderWindow &windowRef)
    {
        Actor::Render(windowRef);
        for (const sf::Sprite &sprite : sprites_)
        {
            windowRef.draw(sprite);
        }
    }

    void BackgroundLayer::Tick(float deltaTime)
    {
        Actor::Tick(deltaTime);
        for (int i = 0; i < sprites_.size(); ++i)
        {
            sf::Sprite &sprite = sprites_[i];
            sf::Vector2f &vel = velocities_[i];

            sprite.setPosition(sprite.getPosition() + vel * deltaTime);
            if (IsSpriteOffScreen(sprite))
            {
                RandomSpriteTexture(sprite);
                RandomSpriteTransform(sprite);

                float velX = RandomRange(minVelocity_.x, maxVelocity_.x);
                float velY = RandomRange(minVelocity_.y, maxVelocity_.y);

                velocities_[i] = sf::Vector2f{velX, velY};
            }
        }
    }

    bool BackgroundLayer::IsSpriteOffScreen(sf::Sprite &sprite) const
    {
        auto bound = sprite.getGlobalBounds();
        auto windowSize = GetWorld()->GetWindowSize();
        auto spritePos = sprite.getPosition();

        if (spritePos.x < -bound.width || spritePos.x > windowSize.x + bound.width)
        {
            return true;
        }

        if (spritePos.y < -bound.height || spritePos.y > windowSize.y + bound.height)
        {
            return true;
        }

        return false;
    }

    shared<sf::Texture> BackgroundLayer::GetRandomTexture() const
    {
        int randomPickIndex = static_cast<int>(RandomRange(0, textures_.size()));
        return textures_[randomPickIndex];
    }
}

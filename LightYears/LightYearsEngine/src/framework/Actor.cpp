#include <box2d/b2_body.h>
#include <iostream>

#include "framework/Actor.h"
#include "framework/Core.h"
#include "framework/AssetManager.h"
#include "framework/MathUtility.h"
#include "framework/World.h"
#include "framework/PhysicsSystem.h"

namespace LightYears
{
    Actor::Actor(World *owningWorld, const std::string &texturePath)
        : owningWorld_{owningWorld},
          hasBeganPlay_{false},
          sprite_{},
          texture_{},
          physicsBody_{nullptr},
          physicsEnabled_{false},
          teamID_{GetNeturalTeamID()}
    {
        SetTexture(texturePath);
    }

    Actor::~Actor()
    {
        LOG("Actor is destory");
    }

    void Actor::BeginPlayInternal()
    {
        if (!hasBeganPlay_)
        {
            hasBeganPlay_ = true;
            BeginPlay();
        }
    }

    void Actor::TickInternal(float deltaTime)
    {
        if (!IsPendingDestory())
        {
            Tick(deltaTime);
        }
    }

    void Actor::BeginPlay()
    {
        // LOG("Actor begin play");
    }

    void Actor::Tick(float deltaTime)
    {
        // LOG("Actor Ticking");
    }

    void Actor::SetTexture(const std::string &texturePath)
    {
        texture_ = AssetManager::Get().LoadTexture(texturePath);
        if (!texture_)
            return;

        sprite_.setTexture(*texture_);

        int textureWidth = texture_->getSize().x;
        int textureHeight = texture_->getSize().y;
        sprite_.setTextureRect(sf::IntRect{sf::Vector2i{}, sf::Vector2i{textureWidth, textureHeight}});
        CenterPivot();
    }

    void Actor::Render(sf::RenderWindow &window)
    {
        if (IsPendingDestory())
            return;

        window.draw(sprite_);
    }

    void Actor::SetActorLocation(const sf::Vector2f &newLoc)
    {
        sprite_.setPosition(newLoc);
        UpdatePhysicsTransform();
    }

    void Actor::SetActorRotation(float newRot)
    {
        sprite_.setRotation(newRot);
        UpdatePhysicsTransform();
    }

    void Actor::AddActorLocationOffset(const sf::Vector2f &offsetAmt)
    {
        SetActorLocation(GetActorLocation() + offsetAmt);
    }

    void Actor::AddActorRotationOffset(float offsetAmt)
    {
        SetActorRotation(GetActorRotation() + offsetAmt);
    }

    sf::Vector2f Actor::GetActorLocation() const
    {
        return sprite_.getPosition();
    }

    float Actor::GetActorRotation() const
    {
        return sprite_.getRotation();
    }

    sf::Vector2f Actor::GetActorForwardDirection() const
    {

        if (useCustomForwardDirection_ == true)
        {
            return forwardDirection_;
        }
        else
        {
            return RotationToVector(GetActorRotation());
        }
    }

    sf::Vector2f Actor::GetActorRightDirection() const
    {
        return (RotationToVector(GetActorRotation() + 90.f));
    }

    /**
     * @brief Set the Actor Forward Direction object, extra function
     *
     * @param newActorForwardDirection
     */
    void Actor::SetActorForwardDirection(float newForwardDirection)
    {
        forwardDirection_ = RotationToVector(newForwardDirection);
        useCustomForwardDirection_ = true;
    }

    /**
     * @brief 设置 Actor 的几何中心点作为旋转(等变换)中心点
     *
     */
    void Actor::CenterPivot()
    {
        sf::FloatRect bound = sprite_.getGlobalBounds();
        sprite_.setOrigin(bound.width / 2, bound.height / 2);
    }

    sf::Vector2u Actor::GetWindowSize() const
    {
        return owningWorld_->GetWindowSize();
    }

    bool Actor::IsActorOutOfWindowBounds(float allowance) const
    {
        float windowWidth = GetWorld()->GetWindowSize().x;
        float windowHeight = GetWorld()->GetWindowSize().y;

        float width = GetActorGlobalBounds().width;
        float height = GetActorGlobalBounds().height;

        sf::Vector2f actorPos = GetActorLocation();

        if (actorPos.x < -width - allowance)
        {
            return true;
        }

        if (actorPos.x > width + windowWidth + allowance)
        {
            return true;
        }

        if (actorPos.y < -height - allowance)
        {
            return true;
        }

        if (actorPos.y > windowHeight + height + allowance)
        {
            return true;
        }

        return false;
    }

    sf::FloatRect Actor::GetActorGlobalBounds() const
    {
        return sprite_.getGlobalBounds();
    }

    void Actor::InitializePhysics()
    {
        if (!physicsBody_)
        {
            physicsBody_ = PhysicsSystem::Get().AddListener(this);
        }
    }

    void Actor::UnInitializePhysics()
    {
        if (physicsBody_)
        {
            PhysicsSystem::Get().RemoveListener(physicsBody_);
            physicsBody_->GetUserData().pointer = reinterpret_cast<uintptr_t>(nullptr);
            physicsBody_ = nullptr;
        }
    }

    void Actor::SetEnablePhysics(bool enable)
    {
        physicsEnabled_ = enable;
        if (physicsEnabled_)
        {
            InitializePhysics();
        }
        else
        {
            UnInitializePhysics();
        }
    }

    void Actor::UpdatePhysicsTransform()
    {
        if (physicsBody_)
        {
            float physicsScale = PhysicsSystem::Get().GetPhysicsScale();                          // 获取转换比例
            b2Vec2 pos{GetActorLocation().x * physicsScale, GetActorLocation().y * physicsScale}; // 位置/坐标转换
            float rotation = DegreesToRadians(GetActorRotation());                                // 旋转角度转换

            physicsBody_->SetTransform(pos, rotation);
        }
    }

    void Actor::OnActorBeginOverlap(Actor *other)
    {
    }

    void Actor::OnActorEndOverlap(Actor *other)
    {
    }

    void Actor::Destroy()
    {
        UnInitializePhysics();
        onActorDestoryed_.Broadcast(this);
        Object::Destroy();
    }

    bool Actor::IsOtherHostile(Actor *other) const
    {
        if (other == nullptr)
            return false;

        if (GetTeamID() == GetNeturalTeamID() || other->GetTeamID() == GetNeturalTeamID())
        {
            return false;
        }

        return GetTeamID() != other->GetTeamID();
    }

    void Actor::ApplyDamage(float amt)
    {
        }

    void Actor::SetTextureRepeated(bool repeated)
    {
        texture_->setRepeated(repeated);
    }
} // namespace LightYears

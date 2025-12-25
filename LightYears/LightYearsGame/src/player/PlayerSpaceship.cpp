#include "player/PlayerSpaceship.h"
#include <SFML/System.hpp>
#include "framework/MathUtility.h"
#include "framework/Core.h"
#include "weapon/BulletShooter.h"
#include "weapon/ThreeWayShooter.h"
#include "weapon/FrontWiper.h"

namespace LightYears
{
    PlayerSpaceship::PlayerSpaceship(World *owningWorld, const std::string &path)
        : Spaceship{owningWorld, path},
          moveInput_{},
          speed_{200.f},
          shooter_{new FrontWiper{this, 0.5f, {50.f, 0.f}}},
          invulnerableTimer_{2.f},
          invulnerable_{true},
          invulnerableFlashInterval_{0.5f},
          invulnerableFlashTimer_{0.f},
          invulnerableFlashDir_{1}
    {
        SetTeamID(1);
        shooter_->SetCurrentLevel(4);
    }

    void PlayerSpaceship::Tick(float deltaTime)
    {
        Spaceship::Tick(deltaTime);
        HandleInput();
        ConsumeInput(deltaTime);
        UpdateInvulnerable(deltaTime);
    }

    void PlayerSpaceship::HandleInput()
    {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
        {
            moveInput_.y = move_up; // -1.f
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
        {
            moveInput_.y = move_dowm; // 1.f
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
        {
            moveInput_.x = move_left; // -1.f
        }

        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
        {
            moveInput_.x = move_right; // 1.f
        }

        ClampInputOnEdge();
        NormalizeInput();

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
        {
            Shoot();
        }
    }

    void PlayerSpaceship::ClampInputOnEdge()
    {
        sf::Vector2f actorLocation = GetActorLocation();

        if (actorLocation.x < 0 && moveInput_.x == move_left)
        {
            moveInput_.x = 0.f;
        }

        if (actorLocation.x > GetWindowSize().x && moveInput_.x == move_right)
        {
            moveInput_.x = 0.f;
        }

        if (actorLocation.y < 0 && moveInput_.y == move_up)
        {
            moveInput_.y = 0.f;
        }

        if (actorLocation.y > GetWindowSize().y && moveInput_.y == move_dowm)
        {
            moveInput_.y = 0.f;
        }
    }

    void PlayerSpaceship::NormalizeInput()
    {
        Normalize(moveInput_);
        // LOG("move input is now: %f, %f", moveInput_.x, moveInput_.y);
    }

    void PlayerSpaceship::ConsumeInput(float deltaTime)
    {
        SetVelocity(moveInput_ * speed_);
        moveInput_.x = moveInput_.y = 0.f;
    }

    void PlayerSpaceship::Shoot()
    {
        if (shooter_)
        {
            shooter_->Shoot();
        }
    }

    /**
     * @brief 为玩家飞船设置新的 Shooter（武器组件）
     *
     * 这是一个“所有权转移接口”
     *
     * - 参数类型使用 `unique<Shooter>&&`，明确表示：
     *   调用者在调用本函数时，必须【放弃】该 Shooter 的所有权
     *
     * - 本函数会：
     *   1. 接管 newShooter 所管理的 Shooter 对象
     *   2. 将其存储为 PlayerSpaceship 内部唯一拥有的 shooter_
     *   3. 调用结束后，调用者传入的 unique<Shooter> 将变为空（nullptr）
     *
     * @param newShooter
     *  右值引用（rvalue reference）形式的 unique<Shooter>，表示“可被安全转移所有权的 Shooter”
     *
     */
    void PlayerSpaceship::SetShooter(unique<Shooter> &&newShooter)
    {
        if (shooter_ && typeid(*shooter_.get()) == typeid(*newShooter.get()))
        {
            shooter_->IncrementLevel();
            return;
        }

        /**
         * 注意：虽然 newShooter 的类型是 `unique<Shooter>&&`
         * 但：
         *   - newShooter 这个“变量名”本身是【左值】
         *   - 如果不显式 std::move，会尝试调用拷贝赋值（编译失败）
         *
         * 因此必须使用 std::move，将其再次转换为右值
         * 表示“我确认要移动它”
         */
        shooter_ = std::move(newShooter);
    }

    void PlayerSpaceship::ApplyDamage(float amt)
    {
        if (!invulnerable_)
        {
            Spaceship::ApplyDamage(amt);
        }
    }

    void PlayerSpaceship::BeginPlay()
    {
        Spaceship::BeginPlay();
        TimerManager::Get().SetTimer(GetWeakRef(), &PlayerSpaceship::StopInvulnerable, invulnerableTimer_);
    }

    void PlayerSpaceship::StopInvulnerable()
    {
        GetSprite().setColor({255, 255, 255, 255});
        invulnerable_ = false;
    }

    void PlayerSpaceship::UpdateInvulnerable(float deltaTime)
    {
        if (!invulnerable_)
            return;

        invulnerableFlashTimer_ += deltaTime * invulnerableFlashDir_;
        if (invulnerableFlashTimer_ < 0 || invulnerableFlashTimer_ > invulnerableFlashInterval_)
        {
            invulnerableFlashDir_ *= -1;
        }

        GetSprite().setColor(LerpColor({255, 255, 255, 64}, {255, 255, 255, 128}, invulnerableFlashTimer_ / invulnerableFlashInterval_));
    }

    PlayerSpaceship::~PlayerSpaceship() = default;
}
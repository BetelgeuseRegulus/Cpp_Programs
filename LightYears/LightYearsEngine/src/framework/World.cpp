#include "framework/Actor.h"
#include "framework/Application.h"
#include "framework/Core.h"
#include "framework/World.h"
#include "gameplay/GameStage.h"
#include "widgets/HUD.h"

namespace LightYears
{
    World::World(Application *owningApp)
        : owningApp_{owningApp},
          beganPlay_{false},
          actors_{},
          pendingActors_{},
          gameStages_{},
          currentStage_{gameStages_.end()}
    {
    }

    void World::BeginPlayInternal()
    {
        if (!beganPlay_)
        {
            beganPlay_ = true;
            BeginPlay();
            InitGameStages();
            StartStages();
        }
    }

    void World::TickInternal(float deltaTime)
    {
#pragma region custom
        if (isBeingDestroyed_)
            return;

#pragma endregion

        for (shared<Actor> actor : pendingActors_)
        {
            actors_.push_back(actor);
            actor->BeginPlayInternal();
        }

        pendingActors_.clear();

        for (auto iter = actors_.begin(); iter != actors_.end();)
        {
            iter->get()->TickInternal(deltaTime);
            ++iter;
        }

        if (currentStage_ != gameStages_.end())
        {
            currentStage_->get()->TickStage(deltaTime);
        }

        Tick(deltaTime);

        if (HUD_)
        {
            if (!HUD_->HasInit())
            {
                HUD_->NativeInit(owningApp_->GetWindow());
            }
            HUD_->Tick(deltaTime);
        }
    }

    sf::Vector2u World::GetWindowSize() const
    {
        return owningApp_->GetWindowSize();
    }

    World::~World()
    {
    }

    void World::BeginPlay()
    {
        LOG("Began Play");
    }

    void World::Tick(float deletTime)
    {
        // LOG("Tick at frame rate %f", 1.f / deletTime);
    }

    void World::Render(sf::RenderWindow &window)
    {
        for (auto &actor : actors_)
        {
            actor->Render(window);
        }
        RenderHUD(window);
    }

    void World::CleanCycle()
    {
        for (auto iter = actors_.begin(); iter != actors_.end();)
        {
            if (iter->get()->IsPendingDestory())
            {
                iter = actors_.erase(iter); // Returns : An iterator pointing to the next element (or end()).
            }
            else
            {
                ++iter;
            }
        }

#pragma region custom
        // 清理待加入列表中标记为待销毁的 Actor
        for (auto iter = pendingActors_.begin(); iter != pendingActors_.end();)
        {
            if (iter->get()->IsPendingDestory())
            {
                iter = pendingActors_.erase(iter);
            }
            else
            {
                ++iter;
            }
        }
#pragma endregion
    }

    void World::BeginDestroy()
    {
        if (isBeingDestroyed_)
            return;

        isBeingDestroyed_ = true;

        // 1. 停止所有游戏阶段
        currentStage_ = gameStages_.end();

        // 2. 标记所有 Actor 为待销毁
        for (auto &actor : actors_)
        {
            if (actor && !actor->IsPendingDestory())
            {
                actor->Destroy();
            }
        }

        // 3. 标记待加入的 Actor 为待销毁
        for (auto &actor : pendingActors_)
        {
            if (actor && !actor->IsPendingDestory())
            {
                actor->Destroy();
            }
        }

        // 4. 清理 HUD
        if (HUD_)
        {
            HUD_->Destroy();
            HUD_.reset();
        }
    }

    void World::AddStage(const shared<GameStage> &newStage)
    {
        gameStages_.push_back(newStage);
    }

    void World::InitGameStages()
    {
    }

    void World::AllGameStageFinished()
    {
        LOG("All Stage Finished");
    }

    void World::NextGameStage()
    {
        currentStage_ = gameStages_.erase(currentStage_);
        if (currentStage_ != gameStages_.end())
        {
            currentStage_->get()->StartStage();
            currentStage_->get()->OnStageFinished_.BindAction(GetWeakRef(), &World::NextGameStage);
        }
        else
        {
            AllGameStageFinished();
        }
    }

    void World::StartStages()
    {
        currentStage_ = gameStages_.begin();

        if (currentStage_ != gameStages_.end())
        {
            currentStage_->get()->StartStage();
            currentStage_->get()->OnStageFinished_.BindAction(GetWeakRef(), &World::NextGameStage);
        }
    }

    bool World::DispathEvent(const sf::Event &event)
    {
#pragma region
        // 如果 World 正在被销毁，不处理事件
        if (isBeingDestroyed_)
            return false;
#pragma endregion

        if (HUD_)
        {
            return HUD_->HandleEvent(event);
        }

        return false;
    }

    void World::RenderHUD(sf::RenderWindow &window)
    {
#pragma region
        // 如果 World 正在被销毁，不渲染
        if (isBeingDestroyed_)
            return;
#pragma endregion

        if (HUD_)
        {
            HUD_->Draw(window);
        }
    }
}
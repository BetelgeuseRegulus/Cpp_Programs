#include <box2d/b2_body.h>
#include <box2d/b2_polygon_shape.h>
#include <box2d/b2_fixture.h>
#include <box2d/b2_contact.h>

#include "framework/PhysicsSystem.h"
#include "framework/Actor.h"
#include "framework/MathUtility.h"

namespace LightYears
{
    unique<PhysicsSystem> PhysicsSystem::physicsSystem_{nullptr};

    PhysicsSystem &PhysicsSystem::Get()
    {
        if (!physicsSystem_)
        {
            physicsSystem_ = std::move(unique<PhysicsSystem>{new PhysicsSystem});
        }

        return *physicsSystem_;
    }

    void PhysicsSystem::Step(float deltaTime)
    {
        ProcessPendingRemoveListeners();
        physicsWorld_.Step(deltaTime, velocityIterations_, positionIterations_);
    }

    b2Body *PhysicsSystem::AddListener(Actor *listener)
    {
        if (listener->IsPendingDestory())
            return nullptr;

        // 定义一个 Box2D 的刚体定义（b2BodyDef）
        b2BodyDef bodyDef;
        // 设置为动态物体
        bodyDef.type = b2_dynamicBody;
        bodyDef.userData.pointer = reinterpret_cast<uintptr_t>(listener);
        bodyDef.position.Set(listener->GetActorLocation().x * GetPhysicsScale(), listener->GetActorLocation().y * GetPhysicsScale());
        bodyDef.angle = DegreesToRadians(listener->GetActorRotation());

        // 创建真实的刚体实例
        b2Body *body = physicsWorld_.CreateBody(&bodyDef);

        // 创建矩形形状
        b2PolygonShape shape;
        auto bound = listener->GetActorGlobalBounds();
        // 设置 碰撞盒
        // Box2D 的坐标中心点是矩形(物体)中心, 而SFML的坐标起始位置是左上角, 所以传入数据为 半宽, 半高
        shape.SetAsBox(bound.width / 2.f * GetPhysicsScale(), bound.height / 2.f * GetPhysicsScale());

        // 创建一个夹具(fixture), 用于描述材质, 是否传感器等
        b2FixtureDef fixtureDef;
        fixtureDef.shape = &shape;
        fixtureDef.density = 1.0f;
        fixtureDef.friction = 0.3f;
        fixtureDef.isSensor = true; // 设置为传感器(只检测, 不产生碰撞)

        // 将夹具附加到刚体上
        body->CreateFixture(&fixtureDef);

        return body;
    }

    void PhysicsSystem::RemoveListener(b2Body *bodyToRemove)
    {
        // TODO: implement removal of physics body
        pendingRemoveListeners_.insert(bodyToRemove);
    }

    void PhysicsSystem::Cleanup()
    {
        physicsSystem_ = std::move(unique<PhysicsSystem>{new PhysicsSystem});
    }

    PhysicsSystem::PhysicsSystem()
        : physicsWorld_{b2Vec2{0.f, 0.f}},
          physicsScale_{0.01f},
          velocityIterations_{8},
          positionIterations_{3},
          contactListener_{},
          pendingRemoveListeners_{}
    {
        physicsWorld_.SetContactListener(&contactListener_);
        physicsWorld_.SetAllowSleeping(false);
    }

    void PhysicsSystem::ProcessPendingRemoveListeners()
    {
        for (auto listener : pendingRemoveListeners_)
        {
            physicsWorld_.DestroyBody(listener);
        }

        pendingRemoveListeners_.clear();
    }

    void PhysicsContactListener::BeginContact(b2Contact *contact)
    {
        Actor *ActorA = reinterpret_cast<Actor *>(contact->GetFixtureA()->GetBody()->GetUserData().pointer);
        Actor *ActorB = reinterpret_cast<Actor *>(contact->GetFixtureB()->GetBody()->GetUserData().pointer);

        if (ActorA && !ActorA->IsPendingDestory())
        {
            ActorA->OnActorBeginOverlap(ActorB);
        }

        if (ActorB && !ActorB->IsPendingDestory())
        {
            ActorB->OnActorBeginOverlap(ActorA);
        }
    }

    void PhysicsContactListener::EndContact(b2Contact *contact)
    {
        Actor *ActorA = nullptr;
        Actor *ActorB = nullptr;

        if (contact->GetFixtureA() && contact->GetFixtureA()->GetBody())
        {
            ActorA = reinterpret_cast<Actor *>(contact->GetFixtureA()->GetBody()->GetUserData().pointer);
        }

        if (contact->GetFixtureB() && contact->GetFixtureB()->GetBody())
        {
            ActorB = reinterpret_cast<Actor *>(contact->GetFixtureB()->GetBody()->GetUserData().pointer);
        }

        if (ActorA && !ActorA->IsPendingDestory())
        {
            ActorA->OnActorEndOverlap(ActorB);
        }

        if (ActorB && !ActorB->IsPendingDestory())
        {
            ActorB->OnActorEndOverlap(ActorA);
        }
    }
}
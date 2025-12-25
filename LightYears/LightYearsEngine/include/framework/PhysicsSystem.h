#pragma once
#include <box2d/b2_world.h>

#include "framework/Core.h"

namespace LightYears
{
    class Actor;

    class PhysicsContactListener : public b2ContactListener
    {
        virtual void BeginContact(b2Contact *contract) override;
        virtual void EndContact(b2Contact *contact) override;
    };

    class PhysicsSystem
    {
    public:
        static PhysicsSystem &Get();

        void Step(float deltaTime);
        b2Body *AddListener(Actor *listener);
        void RemoveListener(b2Body *body);

        float GetPhysicsScale() const { return physicsScale_; }

        static void Cleanup();

    protected:
        PhysicsSystem();

    private:
        void ProcessPendingRemoveListeners();

        static unique<PhysicsSystem> physicsSystem_;

        b2World physicsWorld_;
        float physicsScale_{};
        int velocityIterations_{};
        int positionIterations_{};

        PhysicsContactListener contactListener_{};

        Set<b2Body *> pendingRemoveListeners_;
    };
}
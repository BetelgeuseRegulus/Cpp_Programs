#pragma once

namespace LightYears
{
    class Actor;
    class Shooter
    {
    public:
        void Shoot();

        virtual bool CanShoot() const { return true; }
        virtual bool IsOnCooldown() const { return false; }

        Actor *GetOwner() const { return owner_; }

        int GetCurrentLevel() const { return currentLevel_; }
        virtual void SetCurrentLevel(int level);
        int GetMaxLevel() const { return maxLevel_; }

        virtual void IncrementLevel(int amt = 1);

    protected:
        Shooter(Actor *owner);

    private:
        virtual void ShootImpl() = 0;

    private:
        Actor *owner_{};

        int currentLevel_{};
        int maxLevel_{};
    };
}
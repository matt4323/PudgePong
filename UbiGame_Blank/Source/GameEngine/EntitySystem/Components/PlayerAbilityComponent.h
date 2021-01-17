#pragma once

#include "../Component.h"
#include "HookComponent.h"
#include "NetComponent.h"

namespace Game
{
    class PlayerAbilityComponent : public GameEngine::Component
    {
    private:
            HookComponent* hook = nullptr;
            float dodgeTime = 0.f;
    public:

        virtual void Update() override;
        virtual void OnAddToWorld() override;
    };
}
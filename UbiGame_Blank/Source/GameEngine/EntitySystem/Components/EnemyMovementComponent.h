#pragma once
#include <stdlib.h>
#include "../Component.h"
#include "HookComponent.h"

namespace Game
{
    class EnemyMovementComponent : public GameEngine::Component
    {
        float destination_x = 100;
        float destination_y = 100;
        float timer = 1;
    public:
        virtual void Update() override;
        virtual void OnAddToWorld() override;
        GameEngine::Entity* player = nullptr;
        bool death = false;
        Game::HookComponent*hook = nullptr;
        float rooted = 0.f;
    };
}
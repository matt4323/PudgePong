#pragma once
#include <stdlib.h>
#include "../Component.h"
#include "HookComponent.h"
#include "NetComponent.h"

namespace Game
{
    class EnemyAbilityComponent : public GameEngine::Component
    {
        private:
            HookComponent* hook = nullptr;
        public:
            float timer = (float)(rand() % 5 + 3);
            virtual void Update() override;
            virtual void OnAddToWorld() override;
            GameEngine::Entity* player = nullptr;
    };
}
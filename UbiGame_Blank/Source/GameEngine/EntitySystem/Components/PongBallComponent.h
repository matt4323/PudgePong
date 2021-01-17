#pragma once

#include "../Component.h"

namespace Game
{
    class PongBallComponent : public GameEngine::Component
    {
        public:
            float destination_x=0.f, destination_y=0.f;
            int collided = -1;
            virtual void Update() override;
            virtual void OnAddToWorld() override;
    };
}
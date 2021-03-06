#include "LineComponent.h"
#include <SFML/Window/Keyboard.hpp>   //<-- Add the keyboard include in order to get keyboard inputs
#include <SFML/Window/Mouse.hpp>
#include <SFML/Window/Window.hpp>
#include <iostream>
#include "GameEngine/GameEngineMain.h" //<-- Add this include to retrieve the delta time between frames
#include "PlayerMovementComponent.h"
#include "PlayerAbilityComponent.h"
#include <math.h>

using namespace Game;

void LineComponent::Update()
{
    Component::Update();

    //Grabs how much time has passed since last frame
    const float dt = GameEngine::GameEngineMain::GetTimeDelta();

        //By default the displacement is 0,0
    sf::Vector2f displacement{ 0.0f,0.0f };

    //The amount of speed that we will apply when input is received
    float inputAmount = 125.0f;

    sf::Vector2f windowPos{ static_cast<float>(GetEntity()->window->getPosition().x),  static_cast<float>(GetEntity()->window->getPosition().y) };

    sf::Vector2f destination{ destination_x, destination_y };
    sf::Vector2f pos_diff = destination - GetEntity()->GetPos() - windowPos;

    // Find the length of the pos_diff vector
    float vector_length = sqrt(pos_diff.x * pos_diff.x + pos_diff.y * pos_diff.y);

    //Update the entity position

    sf::Vector2f unit{0.f,1.f};

    float dot = pos_diff.x*unit.x + pos_diff.y*unit.y;
    float det = pos_diff.x*unit.y - pos_diff.y*unit.x;
    float angle = 180*atan(dot/det)/3.14;
    if(pos_diff.x < 0){
        angle += 180;
    }
    GetEntity()->SetRotation(angle);

    sf::Vector2f stretch{ 0, sqrt((displacement.x*displacement.x) + (displacement.y*displacement.y)) };

    if (liveTime > 0) {
        displacement.x += inputAmount * (pos_diff.x / vector_length) * dt;
        displacement.y += inputAmount * (pos_diff.y / vector_length) * dt;
        GetEntity()->SetSize(GetEntity()->GetSize() + stretch);
        liveTime -= dt;
    } else if (retractTime > -0.25f) {
        displacement.x -= inputAmount * (pos_diff.x / vector_length) * dt;
        displacement.y -= inputAmount * (pos_diff.y / vector_length) * dt;
        GetEntity()->SetSize(GetEntity()->GetSize() + stretch);
        retractTime -= dt;
    } else {
        GameEngine::GameEngineMain::GetInstance()->RemoveEntity(GetEntity());
    }
        GetEntity()->SetPos(GetEntity()->GetPos() + displacement);
}

void LineComponent::OnAddToWorld() {}
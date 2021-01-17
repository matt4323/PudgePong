#include "PongBallComponent.h"
#include <SFML/Window/Keyboard.hpp>   //<-- Add the keyboard include in order to get keyboard inputs
#include <SFML/Window/Mouse.hpp>
#include <SFML/Window/Window.hpp>
#include <iostream>
#include "GameEngine/GameEngineMain.h" //<-- Add this include to retrieve the delta time between frames
#include "PlayerMovementComponent.h"
#include "PlayerAbilityComponent.h"
#include <math.h>

using namespace Game;

void PongBallComponent::Update()
{
    Component::Update();

    //Grabs how much time has passed since last frame
    const float dt = GameEngine::GameEngineMain::GetTimeDelta();

        //By default the displacement is 0,0
    sf::Vector2f displacement{ 0.0f,0.0f };

    //The amount of speed that we will apply when input is received
    float inputAmount = 145.0f;

    displacement.x += inputAmount * destination_x * dt;
    displacement.y += inputAmount * destination_y * dt;

    if (collided == 0) {
        destination_x *= -1;
    } else if (collided == 1) {
        destination_y *= -1;
    } else if (collided == 2) {
        destination_x *= -1;
    } else if (collided == 2) {
        destination_y *= -1;
    }

    GetEntity()->SetPos(GetEntity()->GetPos() + displacement);

}

void PongBallComponent::OnAddToWorld() {}
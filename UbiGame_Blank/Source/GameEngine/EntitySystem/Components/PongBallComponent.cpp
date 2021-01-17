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
    float inputAmount = 195.0f;

    if (collided == 0) {
        abs(destination_x);
        destination_x *= -1;
    } else if (collided == 1) {
        abs(destination_y);
        destination_y *= -1;
    } else if (collided == 2) {
        abs(destination_x);
        destination_x *= -1;
    } else if (collided == 3) {
        abs(destination_y);
        destination_y *= -1;
    } 
    collided = -1;

    displacement.x += inputAmount * destination_x * dt;
    displacement.y += inputAmount * destination_y * dt;

    GetEntity()->SetPos(GetEntity()->GetPos() + displacement);
    GetEntity()->SetRotation(GetEntity()->GetRot() + dt*25);
}

void PongBallComponent::OnAddToWorld() {}
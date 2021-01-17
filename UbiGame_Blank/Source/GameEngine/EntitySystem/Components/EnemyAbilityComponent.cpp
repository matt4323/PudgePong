#include "EnemyAbilityComponent.h"
#include <SFML/Window/Mouse.hpp>
#include <SFML/Window/Window.hpp> //shouldnt need these but included them anyways
#include <stdlib.h> //needed for rand
#include <iostream>
#include "GameEngine/GameEngineMain.h" 

using namespace Game;

void EnemyAbilityComponent::Update()
{
    Component::Update();

    const float dt = GameEngine::GameEngineMain::GetTimeDelta();
    timer -= dt;

    if(!GetEntity()->isAbility){

        if(GetEntity()->netDown <= 0.f && timer - dt <= 0.f){
            GetEntity()->hooking = false;
            GetEntity()->netting = true;
            GetEntity()->dodging = false;
            timer = (float)(rand() % 5 + 3);
        }

        else if(GetEntity()->hookDown <= 0.f && timer - dt <= 0.f){
            GetEntity()->hooking = true;
            GetEntity()->netting = false;
            GetEntity()->dodging = false;
            timer = (float)(rand() % 5 + 3);
        }

        GetEntity()->isAbility = GetEntity()->hooking;

    }

    if(GetEntity()->hooking){
        if(hook != nullptr){
            if(hook->retractTime <= 0.f){
                hook = nullptr;
                GetEntity()->hooking = false;
                GetEntity()->isAbility = false;
            }
        } else {
            GameEngine::Entity* e = new GameEngine::Entity();
            GameEngine::GameEngineMain::GetInstance()->AddEntity(e);
            e->SetPos(GetEntity()->GetPos());
            e->SetSize(sf::Vector2f(32.0f, 32.0f));
            hook = static_cast<HookComponent*>(e->AddComponent<HookComponent>());

            GameEngine::SpriteRenderComponent* spriteRender = static_cast<GameEngine::SpriteRenderComponent*>(e->AddComponent<GameEngine::SpriteRenderComponent>());

            spriteRender->SetFillColor(sf::Color::Transparent);
            spriteRender->SetTexture(GameEngine::eTexture::Player);

            sf::Vector2f displacement{ 0.0f,0.0f };

            sf::Vector2f pos_diff = player->GetPos() - e->GetPos();

            float vector_length = sqrt(pos_diff.x * pos_diff.x + pos_diff.y * pos_diff.y);
            
            sf::Vector2f unit{0.f,1.f};

            float dot = pos_diff.x*unit.x + pos_diff.y*unit.y;
                float det = pos_diff.x*unit.y - pos_diff.y*unit.x;
                float angle = 180*atan(dot/det)/3.14;
                if(pos_diff.x < 0){
                    angle += 180;
                }
                e->SetRotation(angle);

            displacement.x += (pos_diff.x / vector_length);
            displacement.y += (pos_diff.y / vector_length);

            hook->liveTime = 2.5f;
            hook->retractTime = 2.1f;
            hook->destination_x = displacement.x;
            hook->destination_y = displacement.y;

            GetEntity()->hookDown = 8.f;

        }
    }

    if (GetEntity()->netting) {
        GameEngine::Entity* e = new GameEngine::Entity();
        GameEngine::GameEngineMain::GetInstance()->AddEntity(e);
        e->SetPos(GetEntity()->GetPos());  // <-- Move its initial position
        e->SetSize(sf::Vector2f(64.0f, 64.0f)); // <-- Make the square bigger
        NetComponent* net = static_cast<NetComponent*>
        (e->AddComponent<NetComponent>());

        GameEngine::SpriteRenderComponent* spriteRender = e->AddComponent<GameEngine::SpriteRenderComponent>();
        
        spriteRender->SetFillColor(sf::Color::Transparent);
        spriteRender->SetTexture(GameEngine::eTexture::Player);

        net->liveTime = 3.5f;
        net->destination_x = player->GetPos().x;
        net->destination_y = player->GetPos().y;
        GetEntity()->netDown = 10.f;
        GetEntity()->netting = false;
    }

    //Use for implementing dodging
    // if (GetEntity()->dodging) {

    //         GetEntity()->dodgeDown = 10.f;
    // }

    if (GetEntity()->hookDown > 0.f) {
        GetEntity()->hookDown -= dt;
    }
    
    if (GetEntity()->netDown > 0.f) {
        GetEntity()->netDown -= dt;
    }
    //add below back in onec dodging is done
    // if (GetEntity()->dodgeDown > 0.f) {
    //     GetEntity()->dodgeDown -= dt;
    // }

}

void EnemyAbilityComponent::OnAddToWorld() {};
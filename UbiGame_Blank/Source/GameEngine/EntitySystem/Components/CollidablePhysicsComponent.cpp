#include "CollidablePhysicsComponent.h"

#include "GameEngine/Util/CollisionManager.h"
#include "GameEngine/EntitySystem/Entity.h"
#include "PongBallComponent.h"
#include "PlayerMovementComponent.h"
#include "HookComponent.h"
#include "EnemyMovementComponent.h"
#include "NetComponent.h"


#include <vector>
#include <iostream>

using namespace GameEngine;

CollidablePhysicsComponent::CollidablePhysicsComponent()
{

}


CollidablePhysicsComponent::~CollidablePhysicsComponent()
{

}


void CollidablePhysicsComponent::OnAddToWorld()
{
	CollidableComponent::OnAddToWorld();
}


void CollidablePhysicsComponent::OnRemoveFromWorld()
{
	CollidableComponent::OnRemoveFromWorld();
}


void CollidablePhysicsComponent::Update()
{
	//For the time being just a simple intersection check that moves the entity out of all potential intersect boxes
	std::vector<CollidableComponent*>& collidables = CollisionManager::GetInstance()->GetCollidables();

	for (int a = 0; a < collidables.size(); ++a)
	{
		CollidableComponent* colComponent = collidables[a];
		if (colComponent == this)
			continue;

		AABBRect intersection;
		AABBRect myBox = GetWorldAABB();
		AABBRect colideBox = colComponent->GetWorldAABB();
		if (myBox.intersects(colideBox, intersection))
		{
			sf::Vector2f pos = GetEntity()->GetPos();
			if (intersection.width < intersection.height)
			{
				if (myBox.left < colideBox.left)
					pos.x -= intersection.width;
				else
					pos.x += intersection.width;
			}
			else
			{
				if (myBox.top < colideBox.top)
					pos.y -= intersection.height;
				else
					pos.y += intersection.height;
			}
			if ((colComponent->type =="wall0" || colComponent->type =="wall1" || colComponent->type =="wall2" 
			|| colComponent->type =="wall3" || colComponent->type =="river") && type=="pudge")
				GetEntity()->SetPos(pos);
			else if (colComponent->type =="pudge" && (type =="wall0" || type =="wall1" 
			|| type =="wall2" || type =="wall3" || type =="river"))
				GetEntity()->SetPos(pos);
			
				sort_collision(colComponent);
		
		}
	}
}

void CollidablePhysicsComponent::sort_collision(CollidableComponent* collider) 
{
	if (collider->type == "wall0" && type =="pongball") {
		GetEntity()->GetComponent<Game::PongBallComponent>()->collided = 0;
	} else if (collider->type == "wall1" && type =="pongball") {
		GetEntity()->GetComponent<Game::PongBallComponent>()->collided = 1;
	} else if (collider->type == "wall2" && type =="pongball") {
		GetEntity()->GetComponent<Game::PongBallComponent>()->collided = 2;
	} else if (collider->type == "wall3" && type =="pongball") {
		GetEntity()->GetComponent<Game::PongBallComponent>()->collided = 3;
	} else if (collider->type == "pudge" && type == "hook") {
		collider->GetEntity()->GetComponent<Game::PlayerMovementComponent>()->death = true;
		collider->GetEntity()->GetComponent<Game::PlayerMovementComponent>()->hook = GetEntity()->GetComponent<Game::HookComponent>();
	} else if (collider->type == "hook" && type =="pudge") {

	} else if (collider->type == "hook" && type =="pongball") {

	} else if (collider->type == "pongball" && type =="hook") {

	} else if (collider->type == "pudge" && type =="pongball") {

	} else if (collider->type == "pongball" && type =="pudge") {

	}
				
}
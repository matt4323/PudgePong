#pragma once
#include "GameEngine/EntitySystem/Entity.h"
#include <string>
#include <SFML/System/Vector2.hpp>
#include <vector>


namespace Game
{
	//Used for storing and controlling all game related entities, as well as providing an entry point for the "game" side of application	
	class PlayerEntity;	

	class GameBoard
	{
	public:
		GameBoard();
		virtual ~GameBoard();
		int enemyDeathCount = 0;
		int numberOfEnemies = 1;
		int currentEnemies = 1;
		int currentPongs = 1;
		void Update();		
		bool IsGameOver() { return false; }

	private:

		void CreatePlayer();
		GameEngine::Entity* m_player;
		//GameEngine::Entity* m_enemy;
		GameEngine::Entity* m_text;
		void CreateText();
		void CreateBackground();
		void CreateEnemy();
		void CreateObstacle(float x_cord, float y_cord, float width, float height, std::string object_type);
		void CreateBall();

	};
}



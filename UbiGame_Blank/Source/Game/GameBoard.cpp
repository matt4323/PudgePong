#include "GameBoard.h"
#include "../GameEngine/EntitySystem/Components/CollidablePhysicsComponent.h"
#include "GameEngine/GameEngineMain.h"
#include "../GameEngine/EntitySystem/Components/PlayerMovementComponent.h"
#include "../GameEngine/EntitySystem/Components/PlayerAbilityComponent.h"
#include "../GameEngine/EntitySystem/Components/EnemyMovementComponent.h"
#include "../GameEngine/EntitySystem/Components/PongBallComponent.h"
#include "../GameEngine/EntitySystem/Components/EnemyAbilityComponent.h"
#include "../GameEngine/EntitySystem/Components/TextRenderComponent.h"

using namespace Game;

void GameBoard::CreatePlayer()
{
	m_player = new GameEngine::Entity();
	GameEngine::GameEngineMain::GetInstance()->AddEntity(m_player);
	
	m_player->SetPos(sf::Vector2f(150.0f, 150.0f));  // <-- Move its initial position
	m_player->SetSize(sf::Vector2f(64.0f, 64.0f)); // <-- Make the square bigger

	m_player->AddComponent<Game::PlayerMovementComponent>();  // <-- Added the movement component to the player

    GameEngine::SpriteRenderComponent* spriteRender = static_cast<GameEngine::SpriteRenderComponent*>
    (m_player->AddComponent<GameEngine::SpriteRenderComponent>());

    spriteRender->SetTexture(GameEngine::eTexture::Player);

    m_player->AddComponent<Game::PlayerAbilityComponent>();
    //Adding CollidingPhysicsComponent to Player
    GameEngine::CollidablePhysicsComponent* collisionTyper = static_cast<GameEngine::CollidablePhysicsComponent*>
        (m_player->AddComponent<GameEngine::CollidablePhysicsComponent>());
    collisionTyper->type="player";

}

void GameBoard::CreateText()
{
    m_text = new GameEngine::Entity();
    GameEngine::GameEngineMain::GetInstance()->AddEntity(m_text);

    m_text->SetPos(sf::Vector2f(100.f, 670.0f));
    m_text->SetSize(sf::Vector2f(300.f, 20.f));

    GameEngine::TextRenderComponent* textRender = static_cast<GameEngine::TextRenderComponent*>
    (m_text->AddComponent<GameEngine::TextRenderComponent>());

    textRender->SetString("Move - Left Click     Hook - Q     Net - W     Dodge - E");
    textRender->SetFont("OptimusPrinceps.ttf");
    textRender->SetCharacterSizePixels(20);
    textRender->SetColor(sf::Color::Black);
}

void GameBoard::CreateScore(){
    m_score = new GameEngine::Entity();
    GameEngine::GameEngineMain::GetInstance()->AddEntity(m_score);

    m_score->SetPos(sf::Vector2f(300.f, 10.0f));
    m_score->SetSize(sf::Vector2f(50.f, 30.f));

    GameEngine::TextRenderComponent* textRender = static_cast<GameEngine::TextRenderComponent*>
    (m_score->AddComponent<GameEngine::TextRenderComponent>());

    std::string score = "Score: " + std::to_string(enemyDeathCount);
    textRender->SetString(score);
    textRender->SetFont("OptimusPrinceps.ttf");
    textRender->SetCharacterSizePixels(30);
    textRender->SetColor(sf::Color::Black);
}

void GameBoard::CreateEnemy(){
    GameEngine::Entity* m_enemy = new GameEngine::Entity();
    GameEngine::GameEngineMain::GetInstance()->AddEntity(m_enemy);
    m_enemy->SetPos(sf::Vector2f(550.0f, (float)(rand() % 600 + 50)));
    m_enemy->SetSize(sf::Vector2f(64.0f, 64.0f));

    Game::EnemyMovementComponent* enemyMovement = static_cast<Game::EnemyMovementComponent*>(m_enemy->AddComponent<Game::EnemyMovementComponent>());

    Game::EnemyAbilityComponent* enemyAbility = static_cast<Game::EnemyAbilityComponent*>(m_enemy->AddComponent<Game::EnemyAbilityComponent>());

    enemyMovement->player = m_player;
    enemyMovement->score = m_score;
    enemyAbility->player = m_player;
    enemyMovement->gameBoard = this;

    GameEngine::SpriteRenderComponent* spriteRender = static_cast<GameEngine::SpriteRenderComponent*>(m_enemy->AddComponent<GameEngine::SpriteRenderComponent>());

    spriteRender->SetTexture(GameEngine::eTexture::Enemy);

    GameEngine::CollidablePhysicsComponent* collisionTyper = static_cast<GameEngine::CollidablePhysicsComponent*>
        (m_enemy->AddComponent<GameEngine::CollidablePhysicsComponent>());
    collisionTyper->type="enemy"; //give enemy pudge(s) collision type of "pudge"

}

void GameBoard::CreateBall(){
    GameEngine::Entity* ball = new GameEngine::Entity();
    GameEngine::GameEngineMain::GetInstance()->AddEntity(ball);
    ball->SetPos(sf::Vector2f(350.0f, (float)(rand() % 500 + 100)));
    ball->SetSize(sf::Vector2f(32.0f, 32.0f));

    Game::PongBallComponent* pong = static_cast<Game::PongBallComponent*>(ball->AddComponent<Game::PongBallComponent>());
    pong->collided = -1;
    pong->destination_x = 0.4;
    pong->destination_y = 0.91652;

    GameEngine::SpriteRenderComponent* spriteRender = static_cast<GameEngine::SpriteRenderComponent*>(ball->AddComponent<GameEngine::SpriteRenderComponent>());

    spriteRender->SetTexture(GameEngine::eTexture::PongBall);

    GameEngine::CollidablePhysicsComponent* collisionTyper = static_cast<GameEngine::CollidablePhysicsComponent*>
        (ball->AddComponent<GameEngine::CollidablePhysicsComponent>());
    collisionTyper->type="pongball"; //give enemy pudge(s) collision type of "pudge"

}

void GameBoard::CreateBackground() {
    GameEngine::Entity* background = new GameEngine::Entity();
    GameEngine::GameEngineMain::GetInstance()->AddEntity(background);

    background->SetPos(sf::Vector2f(350.f, 350.f));
    background->SetSize(sf::Vector2f(700.f, 700.f));

    GameEngine::SpriteRenderComponent* render = static_cast<GameEngine::SpriteRenderComponent*>
    (background->AddComponent<GameEngine::SpriteRenderComponent>());
	m_player->AddComponent<Game::PlayerMovementComponent>();  // <-- Added the movement component to the player
    render->SetTexture(GameEngine::eTexture::Background);
    render->SetZLevel(-1);
    render->SetFillColor(sf::Color::Transparent);
}

GameBoard::GameBoard()
{
	CreatePlayer();
    CreateBackground();
    CreateEnemy();
    CreateBall();
    CreateText();
    CreateScore();
    //ENVIRONMENTAL HITBOXES 
    CreateObstacle(0,350,50,700,"wall0"); //left wall hitbox
    CreateObstacle(350,0,700,50,"wall1"); //top wall hitbox
    CreateObstacle(700,350,50,700,"wall2"); //right wall hitbox
    CreateObstacle(350,700,700,50,"wall3"); //bottom wall hitbox
    CreateObstacle(350,350,145,700,"river"); //River hitbox
    
}


GameBoard::~GameBoard()
{

}



void GameBoard::Update()
{

    if (currentEnemies == 0) {
        currentEnemies = enemyDeathCount/5 + 1;

        for (int i = 0; i < currentEnemies; i++) {
            CreateEnemy();
        }

        if ( enemyDeathCount % 10 == 0 ) {
            CreateBall();
        }
    }
    if (m_player->GetComponent<Game::PlayerMovementComponent>()->death) {
        enemyDeathCount = 0;
		numberOfEnemies = 1;
		currentEnemies = 1;
		currentPongs = 1;
    }
    m_score->GetComponent<GameEngine::TextRenderComponent>()->SetString("Score : " + std::to_string(enemyDeathCount));
}

void GameBoard::CreateObstacle(float x_cord, float y_cord,float width, float height, std::string object_type) 
//fn that makes pongballs, walls and rivers
{
    //Create Obstacle Entity and add into game
    GameEngine::Entity* obstacle = new GameEngine::Entity();  
    GameEngine::GameEngineMain::GetInstance()->AddEntity(obstacle);



    

    //Define Obstacle
    obstacle->SetPos(sf::Vector2f(x_cord, y_cord)); 
    obstacle->SetSize(sf::Vector2f(width, height));

    //Pointer To Identify Hitbox types AND add collider component
    GameEngine::CollidableComponent* collisionTyper = static_cast<GameEngine::CollidableComponent*>
    (obstacle->AddComponent<GameEngine::CollidableComponent>());
   
    
    if(object_type=="pongball") //if a pong ball. Give it a visual.
    {
        GameEngine::SpriteRenderComponent* spriteRender = static_cast<GameEngine::SpriteRenderComponent*>
        (obstacle->AddComponent<GameEngine::SpriteRenderComponent>());
        spriteRender->SetFillColor(sf::Color::Transparent);
        spriteRender->SetTexture(GameEngine::eTexture::PongBall);
        collisionTyper->type = "pongball"; //Give collisionComponent type: pongball
    } 
    else if (object_type=="river")
        collisionTyper->type = "river"; //if river, no collisions
                                           // Give collisionComponent type: river
    else
        collisionTyper->type = object_type; //if wall, no collisions
                                           // Give collisionComponent type: wall


    

}


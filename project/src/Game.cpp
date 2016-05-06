#include "Game.h"

namespace Crescer3D
{
	// forward declaration of static members
	Player* Game::m_Player;
	std::list<Enemy*> Game::m_enemy_list;	
	std::list<Food*> Game::m_food_list;
	
	Camera* Game::m_Camera;
	bool Game::gameNeedReset;
	GameStates Game::gameState;


	Game::Game()
		: System(SystemType::Sys_Game)
	{
		m_Player = new Player();					
		m_Camera = new Camera();

		gameNeedReset=true;
		ResetGame();		
		SetGameStateInit();
	}

	Game::~Game()
	{
		SafeDelete(m_Player);
		//SafeDelete(m_enemy_list);
		//SafeDelete(m_food_list);
		SafeDelete(m_Camera);
	}

	bool Game::Initialize()
	{
				
	}

	bool Game::Update()
	{
		//std::cout << "Game is Running!" << std::endl;
		return true;
	}
	
	bool Game::ShutDown()
	{
		
	}
	

	Player* Game::GetPlayer()
	{
		return m_Player;
	}

	Camera* Game::GetCamera()
	{
		return m_Camera;
	}


	std::list<Enemy*> Game::GetEnemyList()
	{
		return m_enemy_list;
	}
	
	void Game::SetEnemyList(std::list<Enemy*> in_enemy_list)
	{
		m_enemy_list=in_enemy_list;
	}

	std::list<Food*> Game::GetFoodList()
	{
		return m_food_list;
	}
	
	void Game::SetFoodList(std::list<Food*> in_food_list)
	{
		m_food_list=in_food_list;
	}

	void Game::GameOver()
	{
		SetGameStateGameOver();
	}

	void Game::SetGameStatePlay()
	{
		//TODO set initial position of Player
		gameState = Game_Play;
	}

	void Game::SetGameStateInit()
	{
		gameNeedReset=true;
		gameState = Game_Init;
	}
	void Game::SetGameStateGameOver()
	{
		gameState = Game_GameOver;
	}

	bool Game::IsStateInit()
	{
		return gameState==Game_Init;
	}
	bool Game::IsStatePlay()
	{
		return gameState==Game_Play;
	}
	bool Game::IsStateGameOver()
	{
		return gameState==Game_GameOver;
	}

	// set init all postion and reset all
	void Game::ResetGame()
	{
		if(gameNeedReset)
		{
			std::cout <<  "Reset Game" << std::endl;

			HighScore::Reset();

			HighScore::CalculateListScores();
			
					
			//Set the initial Position of the Player
			Game::GetPlayer()->setPosition(0.0,1.0,0.0);
			
			//Create an initial number of enemies and set their positions
			m_enemy_list.clear();
			int number_of_enemies=10;
			for(int number_of_enemy=1; number_of_enemy<=number_of_enemies; number_of_enemy++)
			{	
				Enemy* local_enemy=new Enemy();
				m_enemy_list.push_back( local_enemy);
			}

			int enemy_position_index=3;						
			for(std::list<Enemy*>::iterator list_iter = m_enemy_list.begin(), end=m_enemy_list.end(); list_iter !=end; list_iter++)
			{
				(*list_iter)->setPosition(-enemy_position_index*2,1.0,0.0);
				enemy_position_index++;
			}

			//Create an initial number of food and set the positions
			m_food_list.clear();
			int total_number_of_food=10;
			for(int number_of_food=1; number_of_food<=total_number_of_food; number_of_food++)
			{	
				Food* local_food=new Food();
				m_food_list.push_back( local_food);
			}

			int food_position_index=3;						
			for(std::list<Food*>::iterator list_iter = m_food_list.begin(), end=m_food_list.end(); list_iter !=end; list_iter++)
			{
				(*list_iter)->setPosition(food_position_index*2,2.0,0.0);
				food_position_index++;
			}
			
			//Game::GetEnemy()->setPosition(-3.0,1.0,0.0);
			//Game::GetFood()->setPosition(3.0,2.0,0.0);

			gameNeedReset=false;
		}

	}

}

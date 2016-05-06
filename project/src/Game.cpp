#include "Game.h"

namespace Crescer3D
{
	// forward declaration of static members
	Player* Game::m_Player;
	Enemy* Game::m_Enemy;
	std::list<Enemy*> Game::m_enemy_list;	

	Cube * Game::m_Food;
	Camera* Game::m_Camera;
	bool Game::gameNeedReset;
	GameStates Game::gameState;


	Game::Game()
		: System(SystemType::Sys_Game)
	{
		m_Player = new Player();
		//m_Enemy = new Enemy();			
		m_Food = new Cube();
		m_Camera = new Camera();

		gameNeedReset=true;
		ResetGame();		
		SetGameStateInit();
	}

	Game::~Game()
	{
		SafeDelete(m_Player);
		SafeDelete(m_Enemy);
		SafeDelete(m_Food);
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

	Enemy* Game::GetEnemy()
	{
		return m_Enemy;
	}

	std::list<Enemy*> Game::GetEnemyList()
	{
		return m_enemy_list;
	}
	
	void Game::SetEnemyList(std::list<Enemy*> in_enemy_list)
	{
		m_enemy_list=in_enemy_list;
	}

	Cube* Game::GetFood()
	{
		return m_Food;
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
			std::list<Enemy*> local_enemy_list=GetEnemyList();
			int number_of_enemies=10;
			for(int number_of_enemy=1; number_of_enemy<=number_of_enemies; number_of_enemy++)
			{	
				Enemy* local_enemy=new Enemy();
				m_enemy_list.push_back( local_enemy);
				//std::cout << number_of_enemy<< std::endl;
			}
			//m_enemy_list=local_enemy_list;

			
			std::cout <<  m_enemy_list.size() << std::endl;
			int position_index=3;
			
						

			for(std::list<Enemy*>::iterator list_iter = m_enemy_list.begin(), end=m_enemy_list.end(); list_iter !=end; list_iter++)
			{
				(*list_iter)->setPosition(-position_index,1.0,0.0);
				position_index++;
			}

			
			//Game::GetEnemy()->setPosition(-3.0,1.0,0.0);
			Game::GetFood()->setPosition(3.0,2.0,0.0);

			gameNeedReset=false;
		}

	}

}

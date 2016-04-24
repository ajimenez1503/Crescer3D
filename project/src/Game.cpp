#include "Game.h"

namespace Crescer3D
{
	// forward declaration of static members
	Sphere* Game::m_Player;
	Sphere* Game::m_Enemy;
	Cube * Game::m_Food;
	bool Game::gameNeedReset;
	GameStates Game::gameState;


	Game::Game()
		: System(SystemType::Sys_Game)
	{
		m_Player = new Sphere();
		m_Enemy = new Sphere();
		m_Food = new Cube();
		gameNeedReset=true;
		SetGameStateInit();
	}

	Game::~Game()
	{
		SafeDelete(m_Player);
		SafeDelete(m_Enemy);
		SafeDelete(m_Food);
	}

	bool Game::Update()
	{
		//std::cout << "Game is Running!" << std::endl;
		return true;
	}

	Sphere* Game::GetPlayer()
	{
		return m_Player;
	}

	Sphere* Game::GetEnemy()
	{
		return m_Enemy;
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

	// set init all postion ans reset all
	void Game::ResetGame()
	{
		if(gameNeedReset)
		{
			HighScore::Reset();
			HighScore::CalculateListScores();
			Game::GetPlayer()->setPosition(0.0,1.0,0.0);
			Game::GetEnemy()->setPosition(-3.0,1.0,0.0);
			Game::GetFood()->setPosition(3.0,2.0,0.0);
			gameNeedReset=false;
		}

	}

}

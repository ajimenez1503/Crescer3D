#include "Game.h"

namespace Crescer3D
{
	// forward declaration of static members
	Sphere* Game::m_Player;
	Sphere* Game::m_Enemy;

	GameStates Game::gameState;

	Game::Game()
		: System(SystemType::Sys_Game)
	{
		m_Player = new Sphere();
		m_Enemy = new Sphere();
		SetGameStateInit();
	}

	Game::~Game()
	{
		SafeDelete(m_Player);
		SafeDelete(m_Enemy);
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


	void Game::GameOver()
	{
		SetGameStateGameOver();
	}

	void Game::SetGameStatePlay()
	{
		gameState = Game_Play;
	}

	void Game::SetGameStateInit()
	{
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
}

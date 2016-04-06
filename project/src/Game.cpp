#include "Game.h"

namespace Crescer3D
{
	// forward declaration of static members
	Sphere* Game::m_Player;
	Sphere* Game::m_Enemy;

	Game::Game()
		: System(SystemType::Sys_Game)
	{
		m_Player = new Sphere();
		m_Enemy = new Sphere();
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
}